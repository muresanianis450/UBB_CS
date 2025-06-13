import random

import main
from main import Stooge_sort, Insertion_sort


def generate_list(n: int):
    global rand_list
    rand_list = [random.randint(0, 1000) for _ in range(n)]
    return rand_list
List_1=[34, 918, 948, 590, 290, 989, 643, 224, 613, 343]
List_2=[727, 949, 257, 890, 771, 690, 620, 202, 861, 325]
List_3=[448, 455, 504, 757, 255, 750, 389, 611, 874, 233]
List_4=[393, 490, 543, 492, 52, 656, 327, 388, 673, 556]
List_5=[483, 626, 939, 161, 431, 592, 678, 745, 314, 365]
List_6=[27, 579, 56, 617, 139, 520, 506, 746, 442, 321]
List_7=[1]
List_8=[67, 105, 181, 197, 257, 453, 475, 608, 904, 987]
List_9=[987, 904, 608, 475, 453, 257, 197, 181, 105, 67]
List_10=[11,11,11,11,11,6,11,11,11,11]
""" Sorted Lists
List_1 = [34, 224, 290, 343, 590, 613, 643, 918, 948, 989]
List_2 = [202, 257, 325, 620, 690, 727, 771, 861, 890, 949]
List_3 = [233, 255, 389, 448, 455, 504, 611, 750, 757, 874]
List_4 = [52, 327, 388, 393, 490, 492, 543, 556, 656, 673]
List_5 = [161, 314, 365, 431, 483, 592, 626, 678, 745, 939]
List_6 = [27, 56, 139, 321, 442, 506, 520, 579, 617, 746]"""

def testing_list():
     assert Stooge_sort(List_1,0,len(List_1)-1) == [34, 224, 290, 343, 590, 613, 643, 918, 948, 989]
     assert Stooge_sort(List_2, 0, len(List_2) - 1) == [202, 257, 325, 620, 690, 727, 771, 861, 890, 949]
     assert Insertion_sort(List_3,len(List_3)) == [233, 255, 389, 448, 455, 504, 611, 750, 757, 874]
     assert Insertion_sort(List_4,len(List_4)) == [52, 327, 388, 393, 490, 492, 543, 556, 656, 673]
     assert Insertion_sort(List_5,len(List_5)) ==[161, 314, 365, 431, 483, 592, 626, 678, 745, 939]
     assert Insertion_sort(List_6,len(List_6))==[27, 56, 139, 321, 442, 506, 520, 579, 617, 746]
     assert Insertion_sort([],0) == []
     assert Stooge_sort([],0,0) == []
     assert Stooge_sort(List_7,0,len(List_7)-1) == [1]
     assert Insertion_sort(List_7,len(List_7)) == [1]
     assert Insertion_sort(List_8,len(List_8))== [67, 105, 181, 197, 257, 453, 475, 608, 904, 987]
     assert Stooge_sort(List_8,0,len(List_8)-1) == [67, 105, 181, 197, 257, 453, 475, 608, 904, 987]
     assert Stooge_sort(List_9,0,len(List_9)-1) == [67, 105, 181, 197, 257, 453, 475, 608, 904, 987]
     assert Insertion_sort(List_9,len(List_9))== [67, 105, 181, 197, 257, 453, 475, 608, 904, 987]
     assert Insertion_sort(List_10,len(List_10))==[6,11,11,11,11,11,11,11,11,11]
     assert Stooge_sort(List_10,0,len(List_10)-1) == [6, 11, 11, 11, 11, 11, 11, 11, 11, 11]

testing_list()





