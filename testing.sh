# Testing Script for Sudoku

# Testing cases are described in detail in the print statements and in TESTING.md and in testing.out

# Please note, all tests generated with DEBUG flag on solver enabled, but not on creator.

if ! [ $# -eq 1 ]; then
    echo "Usage: testing.sh <n> where n is the number of fuzztests to generate"
    exit 1
fi

FILE="testing.out"

echo "Begin testing" > $FILE


TEST1="./sudoku"
echo -e "\nTest 1: Testing sudoku with invalid parameters ($TEST1)" >> $FILE 2>&1
$TEST1 >> $FILE 2>&1

TEST2="./sudoku iLikePie"
echo -e "\nTest 2: Testing sudoku with invalid parameters ($TEST2)" >> $FILE 2>&1
$TEST2 >> $FILE 2>&1

TEST3="./sudoku create solve"
echo -e "\nTest 3: Testing sudoku with invalid parameters ($TEST3)" >> $FILE 2>&1
$TEST3 >> $FILE 2>&1

TEST4="./sudoku create"
echo -e "\nTest 4: Ask sudoku to create a puzzle using creator module ($TEST4)" >> $FILE 2>&1
$TEST4 >> $FILE 2>&1

TEST5="./sudoku solve"
echo -e "\nTest 5: Testing null stdin input to solver module ($TEST5)" >> $FILE 2>&1
$TEST5 < /dev/null >> $FILE 2>&1

TEST6="./sudoku solve"
OUT="tests/test1/test1"
echo -e "\nTest 6: Testing sudoku puzzle with a single unique solution ($TEST6) (output written to $OUT-output)" >> $FILE 2>&1
$TEST6 < $OUT > $OUT-output 2>&1
echo "Differences found between output and expected output (if none, below is blank)" >> $FILE 2>&1
diff $OUT-output $OUT-expected >> $FILE 2>&1

TEST7="./sudoku solve"
OUT="tests/test2/test2"
echo -e "\nTest 7: Testing sudoku puzzle with multiple solutions ($TEST7) (output written to $OUT-output)" >> $FILE 2>&1
$TEST7 < $OUT > $OUT-output 2>&1
echo "Differences found between output and expected output (if none, below is blank)" >> $FILE 2>&1
diff $OUT-output $OUT-expected >> $FILE 2>&1

TEST8="./sudoku solve"
OUT="tests/test3/test3"
echo -e "\nTest 8: Testing sudoku puzzle with no solutions ($TEST8) (output written to $OUT-output)" >> $FILE 2>&1
$TEST8 < $OUT > $OUT-output 2>&1
echo "Differences found between output and expected output (if none, below is blank)" >> $FILE 2>&1
diff $OUT-output $OUT-expected >> $FILE 2>&1

TEST9="./sudoku solve"
OUT="tests/test4/test4"
echo -e "\nTest 9: Testing sudoku puzzle with invalid input ($TEST9) (output written to $OUT-output)" >> $FILE 2>&1
$TEST9 < $OUT > $OUT-output 2>&1
echo "Differences found between output and expected output (if none, below is blank)" >> $FILE 2>&1
diff $OUT-output $OUT-expected >> $FILE 2>&1

TEST10="./sudoku solve"
OUT="tests/test5/test5"
echo -e "\nTest 10: Testing sudoku puzzle with bad input format ($TEST10) (output written to $OUT-output)" >> $FILE 2>&1
$TEST10 < $OUT > $OUT-output 2>&1
echo "Differences found between output and expected output (if none, below is blank)" >> $FILE 2>&1
diff $OUT-output $OUT-expected >> $FILE 2>&1

echo -e "\n\nThe following tests call sudoku create and pipe the output to sudoku solve. All should return unique solutions." >> $FILE 2>&1
FUZZTESTCREATE="./sudoku create"
FUZZTESTSOLVE="./sudoku solve"
for INT in $(seq 1 $1)
do
    echo -e "\nFuzztest $INT: $FUZZTEST" >> $FILE 2>&1
    $FUZZTESTCREATE | $FUZZTESTSOLVE >> $FILE 2>&1
done

exit 0