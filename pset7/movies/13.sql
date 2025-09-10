-- escreva uma consulta SQL para listar os nomes de todas as pessoas que estrelaram um filme no qual Kevin Bacon também estrelou.

-- nome das pessoas que atuaram com KEVIN BACON
SELECT people.name FROM people WHERE people.id IN (...);

-- na teoria os ids das pessoas que atuam em algum filme com KEVIN BACON
SELECT stars.person_id
   ...> FROM stars
   ...> JOIN movies ON stars.movie_id = movies_id
   ...> WHERE movies.id IN(...);

-- ID dos filmes em que KEVIN BACON aparece
SELECT movies.id
   ...> FROM movies
   ...> JOIN stars ON movies.id = stars.movie_id
   ...> JOIN people ON stars.person_id = people.id
   ...> WHERE people.name = "Kevin Bacon" AND people.birth = 1958;


-- codigo completo 
SELECT people.name FROM people WHERE people.id IN (
SELECT stars.person_id
FROM stars
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN(
SELECT movies.id
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958)) AND people.name != "Kevin Bacon"; --apenas colocamos um codigo dentro do outro (nas partes com (...))
