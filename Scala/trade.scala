// Part 2 about Buy-Low-Sell-High using Yahoo Financial Data
//===========================================================


// (1) Complete the function that is given a list of floats
// and calculuates the indices for when to buy the commodity 
// and when to sell

def trade_times(xs: List[Double]): (Int, Int) = {

    var minIndex = 0;
    var maxIndex = 0;
    var min = 0;
    var profit: Double = 0;

    for (i <- 0 until xs.size) {
        if (xs(i) < xs(min))
            min = i;
        else if (xs(i) - xs(min) > profit) {
            minIndex = min;
            maxIndex = i;
            profit = xs(i) - xs(min);
        }

    }

    return (minIndex,maxIndex)

}


var a = List(28.0, 18.0, 20.0, 26.0, 24.0)


println(trade_times(a))

// an example
//val prices = List(28.0, 18.0, 20.0, 26.0, 24.0)
//assert(trade_times(prices) == (1, 3), "the trade_times test fails")


// (2) Complete the ``get webpage'' function that takes a
// a stock symbol as argument and queries the Yahoo server
// at
//      // 
// This servive returns a CSV-list that needs to be separated into
// a list of strings.

import io.Source
def get_page(symbol: String): List[String] = {

	val url = "http://ichart.yahoo.com/table.csv?s=" + symbol

	var lst: List[String] = List();

	var str = Source.fromURL(url).getLines.map(_.split(" "))

	//var abc = str.next.mkString

	//println(str.next.mkString)

	while(1 == 1) {

		//something
		try{

			var test = str.next.mkString;
		//println(test)
			if(lst.indexOf(test) != -1)  lst;
			lst:+= test 
		} catch {

			case e: Exception => return lst

		}
		

		//println(lst)

	}


	/*while(true) {

		var test = str.next.mkString
		
		if(lst.indexOf(test) != -1)  lst
		  else  lst: += test

	} */

		//lst: += Source.fromURL(url).mkString.toString;
		//temp = temp.split("\n")

		//println(temp)
		//lst:+= temp 
		
		//println(lst(0))
		

		/*if(lst.indexOf(temp) != -1) {    
           //println(lst)
			return lst
		} */
	lst;
	
}

//get_page("GOOG")





// (3) Complete the function that processes the CSV list
// extracting the dates and anjusted close prices. The
// prices need to be transformed into Doubles.

def process_page(symbol: String): List[(String, Double)] = {

		var localList =  get_page(symbol).drop(1)

		var l: List[String] = List();

		val cols = localList(0).take(1).mkString

		var st = " "

		var counter: Int = 0;

		while(true) {

			try{

			localList(counter).split(",").foreach(aux(_))

			counter = counter + 1;


		} catch {

			case e: Exception => return toReturn

		}

		}

		println(toReturn)

		var alpha: List[(String,Double)] = List();

		alpha;

}

var count = 0;

var toReturn: List[(String, Double)] = List();

var tempString  = "";
var tempDouble: Double = 0.0


def aux(st: String): Unit = {

	if(count > 6) { count = 0; tempString = ""; tempDouble = 0.0; }

	if(count == 0 ) {

		tempString = st

	} 
	if(count == 6) {
		tempDouble =  st.toDouble
	}

	count = count + 1

	if(tempString.equals("") || tempDouble == 0.0) {
		return;
	}

	toReturn:+= (tempString, tempDouble);


}

process_page("GOOG")


var doubleList: List[Double] = List();

def helper(st: String): Unit = {

	if(count > 6) { count = 0; tempString = ""; tempDouble = 0.0; }

	if(count == 2 || count == 3 ) {

		doubleList:+= st.toDouble;

	} 


	count = count + 1

	if(tempString.equals("") || tempDouble == 0.0) {
		return;
	}



}

// (4) Complete the query_company function that obtains the
// processed CSV-list for a stock symbol. It should return
// the dates for when to buy and sell the stocks of that company.

def query_company(symbol: String): (String, String) = {

	var localList =  get_page(symbol).drop(1);

	var counter = 0

	localList(0).split(",").foreach(helper(_))

	println(trade_times(doubleList))

	println(doubleList)

	var me = (" ", " ");

	me;
}


query_company("GOOG")


// some test cases

//query_comp("GOOG")

// some more test cases
/*
val indices = List("GOOG", "AAPL", "MSFT", "IBM", "FB", "YHOO", "AMZN", "BIDU")

for (name <- indices) {
  val times = query_comp(name)
  println(s"Buy ${name} on ${times._1} and sell on ${times._2}")
}
*/


