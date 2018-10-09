#!/usr/bin/python3
import sys
import re
from typing import List, Tuple, Set, Any, Iterable, Collection
import pickle

def main():
    filename = "L7g1"
    if len(sys.argv) > 1:
        filename = sys.argv[1]

    vertices, vertices_r, vertice_count, edge_count = load_vertices(filename, get_r=True)

    topo = topological(vertices, vertice_count)
    print(topo)
    strongs = findComponents(vertices_r, vertice_count, topo)
    print()

    print("grafen", filename, "har", len(strongs), "sterkt sammenhengende komponenter.")
    if len(strongs) < 100:
        print("Komponent\t\tNoder i komponenten")
        for i, v in enumerate(strongs):
            print(i, "\t\t\t\t"+", ".join([str(k) for k in v]))


def findComponents(vertices, vertice_count, order):
    print("finding components")
    nodecomp = [-1 for i in range(vertice_count)]
    comp = 0
    for v in order:
        if nodecomp[v] == -1:
            children = vertices[v]
            nodecomp[v] = comp
            while children:
                c = children.pop()
                if nodecomp[c] == -1:
                    nodecomp[c] = comp
                    children.update(vertices[c])
            comp += 1

    result = [ [] for _ in range(comp) ]
    for i, v in enumerate(nodecomp):
        result[v].append(i)
    return result


def dfs(vertices, startpoint, endpoint, vertice_count):
    notfound = set(range(vertice_count))
    allofem = set(range(vertice_count))
    stack = [ startpoint ]
    path = [ ]
    while stack:
        i = stack.pop(-1)
        if i == -1:  # if backtracking
            path.pop(-1)
            continue
        notfound.discard(i)
        path.append(i)
        children = set(vertices[i])
        if endpoint in children and i != endpoint:
            return path+[endpoint]
        elif children:
            children -= allofem - notfound  # remove found children
            stack.append(-1)  # signal backtrack
            stack.extend(children) # check all children
        else:
            stack.append(-1)

    return []  # no path


def topological(vertices, vertice_count):
    """

    :param vertices:
    :param vertice_count:
    :return:
    """
    print("finding topological")
    notfound = set(range(vertice_count))
    found = set()
    topo = []
    stack = []
    while notfound:
        if not stack:
            stack = [[next(iter(notfound)), False]]  # iterator, and whether backtracking
        i, backtracking = stack.pop(-1)
        if not backtracking and i in notfound:
            notfound.remove(i)
            found.add(i)
            children = set(vertices[i])
            children -= found  # remove found children
            if children:
                stack.append([i, True])
                stack.extend(list(zip(children, [False] * vertice_count)))
            else:
                topo.insert(0, i)
        elif backtracking:
            topo.insert(0, i)
    return topo


def load_vertices(filename: str, get_r: bool = False):
    """
    complexity: Theta(N) where N is lines in file

    :param filename: filename, name of file to load.
    :param get_r: whether to find and return reverse graph
    :return: vertices, where i -> every j in the set in vertices[i]
    :return: vertices_r, vertices for the reverse graph (if getR)
    :return: vertice_count, amount of vertices in the graph
    :return: edge_count, amount of edges in the graph
    """
    """

    """
    entry_format = re.compile("\s?[0-9A-Za-z]+\s?")

    with open(filename) as file:  # get data
        vertice_count, edge_count = entry_format.findall(next(file))
        vertice_count: int = int(vertice_count)
        edge_count: int = int(edge_count)

        vertices = [set() for _ in range(vertice_count)]
        if get_r:
            vertices_r: List[Set[int]] = [set() for _ in range(vertice_count)]

        for line in file:
            to, fro = [int(x) for x in entry_format.findall(line)]
            vertices[to].add(fro)
            if get_r:
                vertices_r[fro].add(to)

        print("loaded vertices")
        if get_r:
            return vertices, vertices_r, vertice_count, edge_count
        else:
            return vertices, vertice_count, edge_count


if __name__ == "__main__":
    main()
