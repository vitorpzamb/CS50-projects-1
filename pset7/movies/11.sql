-- escreva uma consulta SQL para listar os títulos dos cinco filmes com melhor classificação (em ordem)
-- que Chadwick Boseman estrelou, começando com os de maior classificação.
SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN ratings ON movies.id = ratings.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC limit 5;

