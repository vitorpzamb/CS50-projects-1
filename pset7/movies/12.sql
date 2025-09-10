-- escreva uma consulta SQL para listar os títulos de todos os filmes em que Johnny Depp e Helena Bonham Carter estrelaram juntos.
SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name IN ("Johnny Depp", "Helena Bonham Carter")
-- esse codigo em especifico mostra o nome de todos os filmes em que pelo menos um dos atores aparece (alguns filmes podem aparecer mais de uma vez)

--para mostrar todos os filmes em que OS DOIS aparecem precisamos complementar o codigo

--adicionamos as seguintes linhas

GROUP BY movies.title -- aqui agrupamos todos os filmes que ja apareciam (pelo nome),
-- assim nao aparecerao mais filmes mais de uma vez na tabela (mas ainda teremos filmes em que apenas um dos dois apareceu)



-- para adicionar a ultima condicao colocamos a linha a seguir:
HAVING COUNT(DISTINCT people.name) = 2;
-- HAVING eh uma linha que pelo que eu sei ate agora so pode ser colocada depois de um GROUP BY
-- e o count(...) filtra os filmes para apenas filmes que tenham dois atores aparecam***

-- ***por que isso funciona? depois de termos usado a linha WHERE... so temos filmes em que ou Johnny aparece ou a Helena aparece (ou os dois)
-- usamos o GROUP BY... para eliminar duplicatas, e selecionamos apenas os filmes com dois atores (QUE NESSE CASO SERIA OS DOIS CITADOS NO ENUNCIADO)
