# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    with open(sys.argv[1], "r") as file:
        leitor = csv.DictReader(file)
        teams = list(leitor)

    for k in range(len(teams)):
        teams[k]["rating"] = int(teams[k]["rating"])

    counts = {}
    for i in teams:   # i nesse caso seria equivalente a teams[num], i eh um dicionario, so estamos pegando uma parte especifica dele
        counts[i["team"]] = 0

    # TODO: Simulate N tournaments and keep track of win counts
    for j in range(N):
        counts[simulate_tournament(teams)] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    #Simulate a game. Return True if team1 wins, False otherwise.
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    #Simulate a round. Return a list of winning teams.
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams): #return name of winning team
    vencedores = simulate_round(teams)
    if(len(vencedores) == 1):
        return vencedores[0]["team"]
    else:
        teams1 = simulate_tournament(vencedores)
        return teams1


if __name__ == "__main__":
    main()
