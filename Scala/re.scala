// Part 1 about Regular Expression Matching
//==========================================

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


println(nullable(""))

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
println(der('a',r2))
println(der('b',r2))
println(nullable(der('c',r2)) + "   nullable called")


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

println(simp(c))

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





val reg = SEQ(SEQ(CHAR('a'),CHAR('b')),CHAR('c'))
val s = "abc"

println(matcher(reg,s))




// (1e) Complete the function below: it searches (from the left to 
// right) in string s1 all the non-empty substrings that match the 
// regular expression -- these substrings are assumed to be
// the longest substrings matched by the regular expression and
// assumed to be non-overlapping. All these substrings in s1 are replaced
// by s2.

def replace(r: Rexp, s1: String, s2: String): String = {


   
  aux(r,s1,s2,0,s1.length()-1)

  

}

def aux(r: Rexp, s1: String, s2: String, startIndex: Int, endIndex: Int): String = {

  if(matcher(r, s1.substring(startIndex, endIndex))) {

    //match found REPLACE WITH S2

    val s = s1.substring(0,startIndex) + s2 + s1.substring(endIndex, s1.length()-1)
  
    s    
 /*     if(startIndex == endIndex) { s } else {
     //returning s here makes it replace the first occurence
    aux(r,s,s2,endIndex,s.length()-1) 

}
*/
  } else {
 
    aux(r,s1,s2,startIndex,endIndex-1)

  }


}

//Passing as new s1: substring(0, startIndex)+s2+substring(endIndex, s1.length)

val testReg = ALT(STAR(SEQ(CHAR('a'),CHAR('a'))), SEQ(CHAR('b'),CHAR('b')))
//val t = (('a' - 'a').% + ('b','b'))

//val a = " "


println(replace(testReg, "aabb", "c"))


//println(matcher(testReg, "aa") + " matxherr")

// some testing data
// the supposedly 'evil' regular expression (a*)* b
/*
val EVIL = SEQ(STAR(STAR(CHAR('a'))), CHAR('b'))
println(matcher(EVIL, "a" * 1000 ++ "b"))
println(matcher(EVIL, "a" * 1000))


def time_needed[T](i: Int, code: => T) = {
  val start = System.nanoTime()
  for (j <- 1 to i) code
  val end = System.nanoTime()
  (end - start)/(i * 1.0e9)
}

for (i <- 1 to 5000001 by 500000) {
  println(i + " " + "%.5f".format(time_needed(2, matcher(EVIL, "a" * i))))
} */
