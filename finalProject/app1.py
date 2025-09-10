from flask import Flask, flash ,render_template, request, redirect, session
from flask_session import Session
from cs50 import SQL
from helpers import apology, login_required
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import lookup


app = Flask(__name__)

# Sessão e outras configurações
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Impede o navegador de usar páginas armazenadas em cache
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Conexão com o banco
db = SQL("sqlite:///finalProject.db")

@app.route("/add", methods=["GET", "POST"])
@login_required
def add_movie():
    user_id = session["user_id"]

    if request.method == "POST":
        action = request.form.get("action")

        if action == "add":
            title = request.form.get("title")
            rating = request.form.get("rating")
            review = request.form.get("review")

            if not title:
                return apology("must provide movie title")

            # Verifica se o filme já está na lista de 'quero assistir'
            movie = db.execute(
                "SELECT * FROM movies WHERE user_id = ? AND title = ? AND watched = 0",
                user_id, title
            )

            # Busca dados do TMDb
            movie_data = lookup(title)
            if not movie_data:
                return apology("Filme não encontrado na TMDb")

            tmdb_id = movie_data["tmdb_id"]
            poster_path = movie_data["poster_path"] or "https://via.placeholder.com/500x750?text=Sem+Imagem"

            if not movie:
                # Não está na lista, adiciona direto como assistido
                db.execute(
                    "INSERT INTO movies (user_id, title, rating, review, watched, tmdb_id, poster_path) VALUES (?, ?, ?, ?, 1, ?, ?)",
                    user_id,
                    title,
                    rating if rating else None,
                    review if review else None,
                    tmdb_id,
                    poster_path
                )
                flash("Filme adicionado como assistido!")
            else:
                # Está na lista — atualiza para assistido
                db.execute(
                    "UPDATE movies SET watched = 1, rating = ?, review = ?, tmdb_id = ?, poster_path = ? WHERE user_id = ? AND title = ? AND watched = 0",
                    rating if rating else None,
                    review if review else None,
                    tmdb_id,
                    poster_path,
                    user_id,
                    title
                )
                flash("Filme movido para assistidos!")

            return redirect("/")

        elif action == "delete":
            movie_id = request.form.get("movie_id")
            db.execute(
                "DELETE FROM movies WHERE id = ? AND user_id = ? AND watched = 1",
                movie_id,
                user_id
            )
            flash("Filme removido dos assistidos!")
            return redirect("/add")

    else:
        watched = db.execute(
            "SELECT id, title, rating FROM movies WHERE user_id = ? AND watched = 1",
            user_id
        )
        return render_template("watched.html", watched=watched)



@app.route("/my-movies", methods=["GET", "POST"])
@login_required
def my_movies():
    user_id = session["user_id"]

    if request.method == "POST":
        action = request.form.get("action")
        title = request.form.get("title")

        if not title:
            flash("Título não informado.")
            return redirect("/my-movies")

        if action == "add":
            exists = db.execute(
                "SELECT * FROM movies WHERE user_id = ? AND title = ? AND watched = 0",
                user_id, title
            )
            if exists:
                flash("Filme já está na sua lista.")
            else:
                movie_data = lookup(title)
                if not movie_data:
                    return apology("Filme não encontrado na TMDb")

                tmdb_id = movie_data["tmdb_id"]
                poster_path = movie_data["poster_path"]

                db.execute(
                    "INSERT INTO movies (user_id, title, watched, tmdb_id, poster_path) VALUES (?, ?, 0, ?, ?)",
                    user_id, title, tmdb_id, poster_path
                )
                flash("Filme adicionado à sua lista!")
                return redirect("/")

        elif action == "move":
            rating = request.form.get("rating")
            review = request.form.get("review")

            # Buscar dados reais do TMDb
            movie_data = lookup(title)
            if not movie_data:
                return apology("Filme não encontrado na TMDb")

            tmdb_id = movie_data["tmdb_id"]
            poster_path = movie_data["poster_path"]

            db.execute(
                "UPDATE movies SET watched = 1, rating = ?, review = ?, tmdb_id = ?, poster_path = ? WHERE user_id = ? AND title = ? AND watched = 0",
                rating if rating else None,
                review if review else None,
                tmdb_id,
                poster_path,
                user_id,
                title
            )
            flash("Filme movido para assistidos!")
            return redirect("/")

    wishlist = db.execute(
        "SELECT title FROM movies WHERE user_id = ? AND watched = 0",
        user_id
    )
    return render_template("my_movies.html", wishlist=wishlist)



@app.route("/")
@login_required
def index():
    user_id = session["user_id"]

    # Filmes assistidos com avaliação e resenha
    watched = db.execute(
        "SELECT title, rating, review, poster_path FROM movies WHERE user_id = ? AND watched = 1",
        user_id
    )

    # Filmes desejados (my list)
    wishlist = db.execute(
        "SELECT title, poster_path FROM movies WHERE user_id = ? AND watched = 0",
        user_id
    )

    return render_template("index.html", watched=watched, wishlist=wishlist)


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
