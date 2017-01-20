// Part 1 about the 3n+1 conceture
//=================================


//(1) Complete the collatz function below. It should
//    recursively calculate the number of steps needed 
//    until the collatz series reaches the number 1.
//    If needed you can use an auxilary function that
//    performs the recursion. The function should expect
//    arguments in the range of 1 to 1 Million.


def collatz(n: Long): Int = {
	collatz_calculate(n)	 
}


 def collatz_calculate(n: Long, count: Int = 0): Int = {

   	if(n == 1) count + 1
    else {

     if(n % 2 == 0) collatz_calculate(n / 2, count + 1)

     else collatz_calculate(3*n + 1, count + 1)

   }
 }

//(2)  Complete the collatz bound function below. It should
//     calculuate how many steps are needed for each number 
//     from 1 upto a bound and returns the maximum number of
//     steps and the corresponding number that needs that many 
//     steps. You should expect bounds in the range of 1
//     upto 1 million. The first component of the pair is
//     the maximum number of steps and the second is the 
//     corresponding number.

def collatz_max(bnd: Int): (Int, Int) = {

	var temp = 1
	var numberOfsteps  = 0
	var value  = 0

	var call = collatz(temp)

	while(temp != bnd) {
		if(call > numberOfsteps) {
			numberOfsteps = call
			value = temp;
		}

		temp = temp + 1

		call = collatz(temp)

	}
	return (value, numberOfsteps)

} 

println(collatz_max(1000000))

