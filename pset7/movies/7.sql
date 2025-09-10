-- escreva uma consulta SQL para listar todos os filmes lançados em 2010 e suas classificações, em ordem decrescente por classificação.
-- Para filmes com a mesma classificação, ordene-os em ordem alfabética por título.
-- Filmes sem classificação não devem ser incluídos no resultado.
SELECT movies.title, ratings.rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = 2010
ORDER BY ratings.rating DESC, movies.title
