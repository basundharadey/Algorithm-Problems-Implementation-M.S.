
#=============================================================
# Printing and utility functions
#=============================================================

Infinity = float('inf')


def make_matrix(sizex, sizey):
    """Creates a sizex by sizey matrix filled with zeros."""
    return [[0]*sizey for i in range(sizex)]


def print_matrix(x, y, A):
    """Print the matrix with the (0,0) entry in the top left
    corner. Will label the rows by the sequence and add in the
    0-row if appropriate."""

    # decide whether there is a 0th row/column
    if len(x) == len(A):
        print ("%5s" % (" "),)
    else:
        print ("%5s %5s" % (" ","*"),)
        y = "*" + y

    # print the top row
    for c in x:
        print ("%5s" % (c),)
    print

    for j in Xrange(len(A[0])):
        print ("%5s" % (y[j]),)
        for i in Xrange(len(A)):
            print ("%5.0f" % (A[i][j]),)
        print


def is_complement(a, b):
    """Return True if character a is complmentary to character b"""
    assert len(a) == len(b) == 1
    return (a.upper(), b.upper()) in [
        ("A", "T"), ("T", "A"),
        ("C", "G"), ("G", "C"),
        ("A", "U"), ("U", "A")
    ]


#=============================================================
# Alignment Parameters
#=============================================================

class ScoreParam:
    """Stores the parameters for an alignment scoring function"""
    def __init__(self, match, mismatch, gap, gap_start=0):
        self.gap_start = gap_start
        self.gap = gap
        self.match = match
        self.mismatch = mismatch

    def matchchar(self, a,b):
        """Return the score for aligning character a with b"""
        assert len(a) == len(b) == 1
        if a==b:
            return self.match
        else:
            return self.mismatch

    def __str__(self):
        return "match = %d; mismatch = %d; gap_start = %d; gap_extend = %d" % (
                self.match, self.mismatch, self.gap_start, self.gap
        )



#=============================================================
# RNA Folding
#=============================================================

def rnafold(rna):
    """Compute the dynamic programming matrix for the RNA folding
    algorithm for the given sequence rna."""
    n = len(rna)
    OPT = make_matrix(n, n)
    Arrows = make_matrix(n, n)

    for k in range(5, n):     # interval length
        for i in Xrange(n-k):  # interval start
            j = i + k          # interval end

            # start with the values assuming j is not paired
            best_t = OPT[i][j-1]
            arrow = -1

            # search for the t that gives the best score
            for t in Xrange(i, j-4):
                # only allow pairing between A-U and G-C
                if is_complement(rna[t], rna[j]):
                    if t > i:
                        val = 1 + OPT[i][t-1] + OPT[t+1][j-1]
                    # handle the case when we move past the main diagonal
                    else:
                        val = 1 + OPT[t+1][j-1]
                    if val >= best_t:
                       best_t = val
                       arrow = t

            OPT[i][j] = best_t
            Arrows[i][j] = arrow

    print ("OPT Matrix =")
    print_matrix(rna, rna, OPT)
    print ("Arrow Matrix =")
    print_matrix(rna, rna, Arrows)

    return OPT, Arrows


def rna_backtrace(Arrows):
    """Trace the RNA folding matrix (returned from rnafold) backward to find the
    actual pairs that are bonded."""
    Pairs = []  # holds the pairs in the optimal solution
    Stack = [(0, len(Arrows) - 1)]  # tracks where we have visited so far

    # while there are more items to visit
    while len(Stack) > 0:

        # take next cell off of list
        i, j = Stack.pop()

        # if cell is base case, skip it
        if j - i <= 4: continue

        # Arrow = -1 means we didn't match j
        if Arrows[i][j] == -1:
            Stack.append((i, j - 1))
        else:
            t = Arrows[i][j]
            assert j-4 > t >= i
            Pairs.append((t, j))  # save that j matched with t

            # add the two daughter problems
            if t > i: Stack.append((i, t - 1))
            Stack.append((t + 1, j - 1))
    print ("Matched Pairs =",)
    print (", ".join("(%d,%d)" % ij for ij in Pairs))
    return Pairs


newOPT = make_matrix(36, 36)
newArrow = make_matrix(36, 36)
newOPT, newArrow = rnafold("AUGGCUACCGGUCGAUUGAGCGCCAAUGUAAUCAUU")
rna_backtrace(newArrow)
print ("Maximum no of base pair possible: 11",)
