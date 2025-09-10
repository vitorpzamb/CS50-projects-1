-- escreva uma consulta SQL para determinar a avaliação média de todos os filmes lançados em 2012. foi pedido sem cabecalho
.mode list
sqlite> .headers off
sqlite> SELECT AVG(ratings.rating)
   ...> FROM movies
   ...> JOIN ratings ON movies.id = ratings.movie_id
   ...> WHERE movies.year = 2012;
-- saida
sqlite> .headers on
sqlite> .mode column
