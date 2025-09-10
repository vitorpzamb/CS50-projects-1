import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    rows = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0;"
                      , user_id) #usamos group by symbol para juntar todas as acoes por nome (symbol nesse caso)

    #temos que rows nos da linhas em que cada uma delas nos da o nome da acao e o numero de shares que temos delas a seguir
    #vamos percorrer cada uma dessas linhas dando um lookup em cada uma delas para conferirmos o preco atual de cada uma (stocks vai conter esses dados)

    stocks = []
    for row in rows:
        quote = lookup(row["symbol"])
        stocks.append({
            "symbol": row["symbol"],
            "shares": row["total_shares"],
            "price": quote["price"],
            "total": row["total_shares"]*quote["price"]
        })

    stocks_total = sum(stock["total"] for stock in stocks)
    grand_total = cash + stocks_total

    return render_template("index.html", stocks=stocks, cash=cash, total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol")
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                return apology("shares must be positive integer")
        except:
            return apology("shares must be positive integer")

        stock = lookup(symbol)
        if stock is None:
            return apology("invalid symbol")
        total_cost = stock["price"]*shares

        #obtendo o id do usuario
        user_id = session["user_id"]

        #consultando o saldo atual do usuario
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"] #devemos usar os indices mesmo tendo apenas um usar com o user_id (nos eh retornado um dicionario)

        if cash < total_cost:
            return apology("can't afford")
        else:
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                       session["user_id"], stock["symbol"], shares, stock["price"])
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    transactions = db.execute(
    "SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC",
    session["user_id"]
    )
    return render_template("history.html", transactions=transactions)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        #obtemos o symbol via o submit feito no quote.html
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol")
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid symbol")

        return render_template("quoted.html", symbol=stock["symbol"], price=stock["price"])
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        #processar os dados enviados
        username = request.form.get("username")
        if not username:
            return apology("must provide username")
        password = request.form.get("password")
        if not password:
            return apology("must provide password")
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("must return confirmation")
        if password != confirmation:
            return apology("passwords don't match")

        # Gerar hash da senha
        hash = generate_password_hash(password)

        # Tentar inserir no banco de dados
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except ValueError:
            return apology("username already exists")

        #retorna para login
        return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must select a symbol")
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                    return apology("shares must be positive integer")
        except:
            return apology("shares must be positive integer")

        qtd = db.execute("SELECT SUM(shares) AS total_shares FROM transactions WHERE user_id = ? AND symbol = ?;",
                        user_id, symbol)[0]["total_shares"]

        if shares > qtd:
            return apology("too many shares")

        price = lookup(symbol)["price"]
        total_sale = shares*price

        #vamos inserir uma transacao negativa (representando a venda)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol, -shares, price)

        return redirect("/")

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_sale, user_id)
    else:
        stocks = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0;",
                            session["user_id"])
        return render_template("sell.html", stocks=stocks)
