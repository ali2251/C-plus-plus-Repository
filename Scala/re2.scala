// Part 2 about Regular Expression Matching
//==========================================

// copy over all code from re.scala

abstract class Rexp
case object ZERO extends Rexp
case object ONE extends Rexp
case class CHAR(c: Char) extends Rexp
case class ALT(r1: Rexp, r2: Rexp) extends Rexp   // alternative 
case class SEQ(r1: Rexp, r2: Rexp) extends Rexp   // sequence
case class STAR(r: Rexp) extends Rexp             // star


// some convenience for typing in regular expressions

import scala.language.implicitConversions    
import scala.language.reflectiveCalls 

def charlist2rexp(s: List[Char]): Rexp = s match {
  case Nil => ONE
  case c::Nil => CHAR(c)
  case c::s => SEQ(CHAR(c), charlist2rexp(s))
}
implicit def string2rexp(s: String): Rexp = charlist2rexp(s.toList)

implicit def RexpOps (r: Rexp) = new {
  def | (s: Rexp) = ALT(r, s)
  def % = STAR(r)
  def ~ (s: Rexp) = SEQ(r, s)
}

implicit def stringOps (s: String) = new {
  def | (r: Rexp) = ALT(s, r)
  def | (r: String) = ALT(s, r)
  def % = STAR(s)
  def ~ (r: Rexp) = SEQ(s, r)
  def ~ (r: String) = SEQ(s, r)
}

val digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
val sign = "+" | "-" | ""
val number = sign ~ digit ~ digit.% 

// (1a) Complete the function nullable according to
// the definition given in the coursework; this 
// function checks whether a regular expression
// can match the empty string

def nullable (r: Rexp) : Boolean = r match {
  case ZERO => false
  case ONE => true
  case CHAR(_) => false
  case ALT(r,s) => nullable(r) || nullable(s)
  case SEQ(r,s) => nullable(r) && nullable(s)
  case STAR(r) => true  

} 


//println(nullable(""))

// (1b) Complete the function der according to
// the definition given in the coursework; this
// function calculates the derivative of a 
// regular expression w.r.t. a character

def der (c: Char, r: Rexp) : Rexp = r match {
  case ZERO => ZERO
  case ONE => ZERO
  case CHAR(d) => if(c == d) ONE else ZERO
  case ALT(r,s) => ALT(der(c,r), der(c,s))
  case SEQ(r,s) => if(nullable(r))  ALT(SEQ(der(c,r),s), der(c,s)) else SEQ(der(c,r),s)
  case STAR(r) => SEQ(der(c,r),STAR(r))    
}

val r = SEQ(SEQ("a","b"),"c")
val r1 = der('a',r)
val r2 = der('b',r1)
//println(der('a',r2))
//println(der('b',r2))
//println(nullable(der('c',r2)) + "   nullable called")


// (1c) Complete the function der according to
// the specification given in the coursework; this
// function simplifies a regular expression;
// however it does not simplify inside STAR-regular
// expressions

def simp(r: Rexp) : Rexp = r match {
  
  case SEQ(r1,r2) => {
    val a = simp(r1)
    val b = simp(r2)
    (a,b) match {
      case (a,ZERO) => ZERO
      case (ZERO,b) => ZERO
      case (a,ONE) => simp(a)
      case (ONE,b) => simp(b)
      case _ => {
         if(a == r1 && b == r2) SEQ(a,b) else simp(SEQ(a,b))
      }
    }

  }
  case ALT(r1,r2) => {

    val a = simp(r1)
    val b = simp(r2)

    (a,b) match {
      case (a,ZERO) => simp(a)
      case (ZERO,b) => simp(b)
      case _ => if(a == b) a else if(a == r1 && b == r2) ALT(a,b) else simp(ALT(a,b))      

    }
 

  } 

  case _ => r


}

//case ALT(q,s) => if(q == s) simp(q) else ALT(simp(q),simp(s))

val a = SEQ(ALT(CHAR('1'),ZERO),ONE)

val b = ALT(a, ALT(ALT(ONE,CHAR('2')), CHAR('3')))

val c = SEQ(b, SEQ(CHAR('3'),ZERO))

val test = SEQ(ALT(ZERO,ZERO),ONE)

//println(simp(c))

//(r1 + 0) ~ 1 + ((1 + r2) + r3) ~ (r3 ~ 0)



// (1d) Complete the two functions below; the first 
// calculates the derivative w.r.t. a string; the second
// is the regular expression matcher taking a regular
// expression and a string and checks whether the
// string matches the regular expression

def ders (s: List[Char], r: Rexp) : Rexp = s match {
  case Nil => r
  case c::cs => ders(cs,simp(der(c,r)))  
}



def matcher(r: Rexp, s: String): Boolean = {

  val derivative = ders(s.toList, r)

  if(nullable(derivative) == true) true else false

}




// (2a) Complete the function iterT which needs to
// be tail-recursive(!) and takes an integer n, a 
// function f and an x as arguments. This function 
// should iterate f n-times starting with the 
// argument x.

import scala.annotation.tailrec

//@tailrec
/*def iterT[A](n: Int, f: A => A, x: A): A = {


	if(n == 0) x
	else iterT(n-1,f,f(x))
	


}*/
@tailrec
def iterT[A](n: Int, f: A => A, x: A): A = n match {
  case 0 => x
  case _ => iterT(n-1,f,f(x))
}


def square(a: Int): Int = {
  println(a);
   a * a;
}

iterT(3,square,2)


// (2b) Complete the size function for regular
// expressions 

def size(r: Rexp): Int = r match {
	case ZERO => 1
	case ONE => 1
	case CHAR(_) => 1
	case ALT(r,s) => 1 + size(r) + size(s)
	case SEQ(r,s) => 1 + size(r) + size(s)
	case STAR(r) => 1 + size(r)   

}

// two testcases about the sizes of simplified and 
// un-simplified derivatives

//val EVIL = SEQ(STAR(STAR(CHAR('a'))), CHAR('b'))
//println(size(iterT(20, (r: Rexp) => der('a', r), EVIL)))        // should produce 7340068
//println(size(iterT(20, (r: Rexp) => simp(der('a', r)), EVIL)))  // should produce 8



// (2c) Complete the fixpoint function below.

@tailrec
def fixpT[A](f: A => A, x: A): A = {

	if(f(x) == x) x
	else fixpT(f,f(x))


}



// testcases


//the Collatz function from CW 6 defined as fixpoint
/*
def ctest(n: Long): Long =
  if (n == 1) 1 else
    if (n % 2 == 0) n / 2 else 3 * n + 1

// should all produce 1 
//println(fixpT(ctest, 97L))
//println(fixpT(ctest, 871L))
//println(fixpT(ctest, 77031L))




// the same function on strings using the regular expression
// matcher
   
def foo(s: String): String = {
  if (matcher("a", s)) "a" else
  if (matcher("aa" ~ STAR("aa"), s)) s.take(s.length / 2) 
  else "a" ++ s * 3
} */

// should all produce "a" 
//println(fixpT(foo, "a" * 97))
//println(fixpT(foo, "a" * 871))