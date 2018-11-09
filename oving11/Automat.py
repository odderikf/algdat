from typing import List, TypeVar
class Automat:
    def __init__(self, inputs: str, accepts: List[int], nexts: List[List[int]]):
        self.inputs = inputs
        self.accepts = accepts
        self.nexts = nexts

    def sjekkInput(self, commands: str):
        state = 0
        for i in commands:
            state = self.nexts[state][self.inputs.index(i)]
        return state in self.accepts
    

a = Automat("01", [1], [[0,1], [1,2], [2,2]])
b = Automat("ab", [4], [[1,2], [3,4], [4,3], [3,3], [4,4]])

print("a:")
print("input:","expect:","actual:", sep="\t\t")
print("010", True, a.sjekkInput("010"), sep="\t\t")
print("111", False, a.sjekkInput("111"), sep="\t\t")
print("010110", False, a.sjekkInput("010110"), sep="\t\t")
print()
print("b:")
print("input:","expect:","actual:", sep="\t\t")
print("abbb", True, b.sjekkInput("abbb"), sep="\t\t")
print("aaab", False, b.sjekkInput("aaab"), sep="\t\t")
print("babab", True, b.sjekkInput("babab"), sep="\t\t")
