#!/usr/bin/python

# MIT License

# Copyright (c) 2021 Tomasz Dorau, 

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# https://www.codechef.com/problems/CONSSTR

import sys
from math import floor

class string_traverser:
    def __init__(self, str):
        self.string = str

    def is_sufsuf(self, start_idx, end_idx):
        assert start_idx <= end_idx
        if 2 * start_idx - end_idx < 0:
            return False
        return self.string[start_idx : end_idx] == self.string[2 * start_idx - end_idx : start_idx]

    def find_suffixes(self, end_idx):
        out_list = []
        for i in range(floor(end_idx / 2), end_idx):
            if self.is_sufsuf(i, end_idx):
                out_list.append(i)
        return out_list

    def find_min_length(self):
        return [ self.string[:min(self.leafs)], min(self.leafs)]

    def get_min_initial(self):
        input_queue = [ len(self.string) ]
        self.leafs = []
        self.solutions = dict()
        while input_queue:
            next = input_queue.pop()
            nodes = self.find_suffixes(next)
            self.solutions[next] = nodes
            if nodes:
                input_queue += nodes
            else:
                self.leafs.append(next)
        [res, length] = self.find_min_length()
        self.print_solution(length)
        return res

    def solution_path_find(self, num):
        inverted = dict()
        for key in self.solutions:
            for value in self.solutions[key]:
                if value in inverted:
                    inverted[value].append(key)
                else:
                    inverted[value] = [ key ]
        path = []
        length = num
        while True:
            path = [ length ] + path
            if length in inverted:
                length = inverted[length][0]
            else:
                break
        for i in path:
            print(self.string[:i])

    def print_solution(self, length):
        self.solution_path_find(length)

def main(s):
    with open(s) as input:
        for line in input.readlines()[1:]: 
            print(f'solution is: {string_traverser(line.strip()).get_min_initial()}')

if __name__ == "__main__":
    main(sys.argv[1])
