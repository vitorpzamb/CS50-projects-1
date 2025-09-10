-- escreva uma consulta SQL para listar os nomes de todas as pessoas que estrelaram um filme lançado em 2004, ordenado por ano de nascimento.
-- Se uma pessoa apareceu em mais de um filme em 2004, ela só deve aparecer uma vez nos resultados.
SELECT DISTINCT(people.name)
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth;
