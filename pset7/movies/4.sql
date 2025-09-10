-- escreva uma consulta SQL para determinar o número de filmes com uma classificação IMDb de 10,0. necessario saida sem cabecalho
sqlite> .mode list
sqlite> .headers off
sqlite> SELECT COUNT(movies.title)
   ...> FROM movies
   ...> JOIN ratings ON movies.id = ratings.movie_id
   ...> WHERE ratings.rating = 10;


-- .... saida da consulta
sqlite> .headers on
sqlite> .mode column --usamos esses comandos para voltar para a configuracao original
