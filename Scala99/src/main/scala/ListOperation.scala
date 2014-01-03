
object ListOperation {

  // P01 Find the last element of a list
  def last[T](ls: List[T]): T = ls match { // nice pattern matching
    case h :: Nil => h
    case _ :: tail => last(tail)
    case _ => throw new NoSuchElementException // remember this
  }

  // P02 Find the last but one element of list
  // builtin: ls.init.head
  def penultimate[T](ls: List[T]): T = ls match {
    case h :: _ :: Nil => h
    case _ :: tail => penultimate(tail) // why not match x :: Nil ?
    case _ => throw new NoSuchElementException
  }

  // lastN
  // builtin: ls takeRight(n) head
  def lastN[T](n: Int, ls: List[T]): T = {
    // use two list
    def lastN[T](n: Int, curList: List[T], resList: List[T]): T = curList match {
      case Nil if n > 0 => throw new NoSuchElementException
      case Nil => resList.head
      case _ :: tail =>
        lastN(n - 1,
          tail,
          if (n > 0) resList else resList.tail)
    }
    if (n <= 0) throw new IllegalArgumentException // exception handling
    else lastN(n, ls, ls)
  }

  // P03 Kth element of a list
  def nth[T](n: Int, ls: List[T]): T = (n, ls) match {
    case (0, h :: _) => h
    // n < 0 will also match this, and finally lead to NoSuchElementException 
    case (n, _ :: tail) => nth(n - 1, tail)
    case (_, Nil) => throw new NoSuchElementException
  }

  def main(args: Array[String]) = {
  }
}