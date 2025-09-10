from flask import redirect, render_template, session
from functools import wraps
import requests

def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code

def login_required(f):
    """Decorator to require login for certain routes"""
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function

TMDB_API_KEY = "0e2d6e26c374029beb82701a43f9a86b"  # substitua pela sua chave real

def lookup(title):
    """Busca filme pelo título na API do TMDb"""
    try:
        url = "https://api.themoviedb.org/3/search/movie"
        params = {
            "api_key": TMDB_API_KEY,
            "query": title,
            "language": "pt-BR"
        }
        response = requests.get(url, params=params)
        response.raise_for_status()
        data = response.json()

        # Pega o primeiro resultado relevante
        movie = data["results"][0]

        return {
            "tmdb_id": movie["id"],
            "title": movie["title"],
            "poster_path": f"https://image.tmdb.org/t/p/w500{movie['poster_path']}" if movie.get("poster_path") else None
        }

    except (requests.RequestException, KeyError, IndexError):
        return None
