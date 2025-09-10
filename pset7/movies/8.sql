-- escreva uma consulta SQL para listar os nomes de todas as pessoas que estrelaram Toy Story.
SELECT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = "Toy Story"
