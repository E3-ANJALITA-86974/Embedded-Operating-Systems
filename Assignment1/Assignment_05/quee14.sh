#!/bin/bash

echo "Enter the basic salary:"
read salary

DA=$(echo "scale=3; $salary * 0.40" | bc)
HRA=$(echo "scale=3; $salary * 0.20" | bc)
total=$(echo "scale=3; $salary + $DA + $HRA" | bc)

echo "Dearness Allowance (DA): $DA"
echo "House Rent Allowance (HRA): $HRA"
echo "Total Salary: $total"

