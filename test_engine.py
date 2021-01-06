
# 1000 8 white
# 10000 16 black
# piece encoding
# 001 1 pawn +
# 010 2 pawn -
# 011 3 king
# 100 4 knight
# 101 5 bishop
# 110 6 rook
# 111 7 queen

# 1000 | 001 = 1001 9 white pawn
# 1000 | 011 = 1011 11  white king
# 1000 | 100 = 1100 12 white knight
# 1000 | 101 = 1101 13 white bishop
# 1000 | 110 = 1110 14 white rook
# 1000 | 111 = 1111 15 white queen

# 10000 | 010 = 10010 18 black pawn
# 10000 | 011 = 10011 19 black king
# 10000 | 100 = 10100 20 black knight
# 10000 | 101 = 10101 21 black bishop
# 10000 | 110 = 10110 22 black rook
# 10000 | 111 = 10111 23 black queen

board = [
    22, 20, 21, 23, 19, 21, 20, 22, 0,  0,  0,  0,  0,  0,  0,  0,
    18, 18, 18, 18, 18, 18, 18, 18, 0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    9,  9,  9,  9,  9,  9,  9,  9,  0,  0,  0,  0,  0,  0,  0,  0,
    14, 12, 13, 15, 11, 13, 12, 14, 0,  0,  0,  0,  0,  0,  0,  0,
]
notation = [
    'a8', 'b8', 'c8', 'd8', 'f8', 'g8', 'h8', 'i8', 'j8', 'k8', 'l8', 'm8', 'n8', 'o8', 'p8',
    'a7', 'b7', 'c7', 'd7', 'f7', 'g7', 'h7', 'i7', 'j7', 'k7', 'l7', 'm7', 'n7', 'o7', 'p7',
    'a6', 'b6', 'c6', 'd6', 'f6', 'g6', 'h6', 'i6', 'j6', 'k6', 'l6', 'm6', 'n6', 'o6', 'p6',
    'a5', 'b5', 'c5', 'd5', 'f5', 'g5', 'h5', 'i5', 'j5', 'k5', 'l5', 'm5', 'n5', 'o5', 'p5',
    'a4', 'b4', 'c4', 'd4', 'f4', 'g4', 'h4', 'i4', 'j4', 'k4', 'l4', 'm4', 'n4', 'o4', 'p4',
    'a3', 'b3', 'c3', 'd3', 'f3', 'g3', 'h3', 'i3', 'j3', 'k3', 'l3', 'm3', 'n3', 'o3', 'p3',
    'a2', 'b2', 'c2', 'd2', 'f2', 'g2', 'h2', 'i2', 'j2', 'k2', 'l2', 'm2', 'n2', 'o2', 'p2',
    'a1', 'b1', 'c1', 'd1', 'f1', 'g1', 'h1', 'i1', 'j1', 'k1', 'l1', 'm1', 'n1', 'o1', 'p1',

]
move_offsets = [
    15,  16,  17,   0,
    15, -16, -17,   0,
     1,  16,  -1, -16,   0,
     1,  16,  -1, -16,  15, -15,  17, -17,   0, 
    14, -14,  18, -18,  31, -31,  33, -33,   0,
     3,  -1,  12,  21,  16,  7, 12  
]
pieces = ".-pknbrq-P-KNBRQ"

def print_board():
    index = 0
    while index < 128:
        # sq is on board
        if(index & 0x88) == 0:
            piece = board[index]
            print(pieces[piece & 15], end=' ')
            index += 1
        else:
            print()
            index += 8

def search(side):
    #move generator
    index = 0
    
    #loop over board squares
    while (index<128):
        if (index & 0x88) == 0: #makes sure the piece is on the board
            piece = board[index]

            if (piece & side):
                print(pieces[piece & 15], end = ' ')
        index += 1
white = 8   #  1000
black = 16  # 10000
search(white)