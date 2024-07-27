read -p "Enter a number: " num

sum=0
temp=$num
n=${#num}
#while loop initialize
while [ $temp -gt 0 ]; do
  digit=$((temp % 10))
  temp=$((temp / 10))
  sum=$((sum + digit**n))
done

# Checking
if [ $sum -eq $num ]; then
  echo "$num is an Armstrong number."
else
  echo "$num is not an Armstrong number."
fi
