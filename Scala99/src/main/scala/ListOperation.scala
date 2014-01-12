
object ListOperation {

  ////////////////////////////////////////////////////////////////////////////////
  // P01 Find the last element of a list
  def last[T](ls: List[T]): T = ls match { // nice pattern matching
    case h :: Nil => h
    case _ :: tail => last(tail)
    case _ => throw new NoSuchElementException // remember this
  }
  ////////////////////////////////////////////////////////////////////////////////
  // P02 Find the last but one element of list
  // builtin: ls.init.head
  def penultimate[T](ls: List[T]): T = ls match {
    case h :: _ :: Nil => h
    // it first match x :: Nil, then lead to penultimate(Nil)
    case _ :: tail => penultimate(tail)
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

  ////////////////////////////////////////////////////////////////////////////////
  // P03 Kth element of a list
  def nth[T](n: Int, ls: List[T]): T = (n, ls) match {
    case (0, h :: _) => h
    // n < 0 will also match this, and finally lead to NoSuchElementException 
    case (n, _ :: tail) => nth(n - 1, tail)
    case (_, Nil) => throw new NoSuchElementException
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P04 Find the number of element in a list
  def lengthRecursive[T](ls: List[T]): Int = ls match {
    case Nil => 0
    case _ :: tail => 1 + lengthRecursive(tail)
  }

  // Tail recursive solution. Theoretically more efficient; with tail-call
  // elimination in the computer, this would run in constant space.
  // Unfortunately, the JVM doesn't do tail-call elimination in the general
  // case. Scala *will* do it if the method is either final or is a local
  // function. In this case, `lengthR` is a local function, so it would 
  // be properly optimized.
  // http://blog.richdougherty.com/2009/04/tail-calls-tailrec-and-trampolines.html
  def lengthTailRecursive[T](ls: List[T]): Int = {
    // no need [T]
    // local function, tail-call optimized
    def lengthR(result: Int, ls: List[T]): Int = ls match {
      case Nil => result
      case _ :: tail => lengthR(result + 1, tail)
    }
    lengthR(0, ls)
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P05 Reverse a list
  // Simple recursive, O(n^2)!
  def reverse[T](ls: List[T]): List[T] = ls match {
    case Nil => Nil
    case h :: tail => reverse(tail) ::: List(h)
  }

  // Tail recursive
  def reverseTailRecursive[T](ls: List[T]): List[T] = {
    def reverseR(result: List[T], curList: List[T]): List[T] = curList match {
      case Nil => result
      case h :: tail => reverseR(h :: result, tail)
    }
    reverseR(Nil, ls)
  }

  // Pure functional
  def reverseFunctional[T](ls: List[T]): List[T] = {
    // can't pass Nil, since it's List[Nothing]
    ls.foldLeft(List[T]()) { (r, h) => h :: r }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P06 Find out whether a list is a palindrome
  def isPalindrome[T](ls: List[T]): Boolean = ls == ls.reverse

  ////////////////////////////////////////////////////////////////////////////////
  // P07 Flatten a nested list structure
  def flatten(ls: List[Any]): List[Any] = ls flatMap { // nice flatMap
    case ms: List[_] => flatten(ms)
    case e => List(e)
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P08 Eliminate consecutive duplicates of list element
  def compress[T](ls: List[T]): List[T] = ls match {
    case Nil => Nil
    case h :: tail => h :: compress(tail.dropWhile(_ == h))
  }

  // Tail Recursive
  def compressTailRecursive[T](ls: List[T]): List[T] = {
    def compressR(result: List[T], curList: List[T]): List[T] = curList match {
      // use result ::: List(h) will lead to O(n^2)
      // so use h :: result and reverse at last
      case h :: tail => compressR(h :: result, tail.dropWhile(_ == h))
      case Nil => result.reverse
    }
    compressR(Nil, ls)
  }

  // Functional
  def compressFunctional[T](ls: List[T]): List[T] = {
    ls.foldRight(List[T]()) {
      case (e, Nil) => List(e) // Nil match List[T]()
      case (e, r) => if (e == r.head) r else e :: r
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P09 Pack consecutive duplicates of list elements into sublists
  // use span instead of takeWhile, dropWhile!
  def pack[T](ls: List[T]): List[List[T]] = ls match {
    case h :: tail => {
      val (prev, next) = tail.span(_ == h)
      (h :: prev) :: pack(next)
    }
    case Nil => List[List[T]]()
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P10 Run-length encoding of a list
  def encode[T](ls: List[T]): List[(Int, T)] = ls match {
    case Nil => List()
    case h :: tail => {
      val (prev, next) = tail.span(_ == h)
      (1 + prev.length, h) :: encode(next)
    }
  }
  // or 
  // pack(ls) map { e => (e.length, e.head) }

  ////////////////////////////////////////////////////////////////////////////////
  // P11 Modified run-length encoding
  def encodeModified[T](ls: List[T]): List[Any] = ls match {
    case a :: b :: tail if (a == b) => {
      val (prev, next) = tail.span(_ == a)
      (2 + prev.length, a) :: encodeModified(next)
    }
    case h :: tail => h :: encodeModified(tail)
    case _ => Nil
  }
  // or
  // encode(ls) map { e => if (e._1 == 1) e._2 else e}

  // A typesafe version
  // But where is Either type used for?
  def encodeModified2[T](ls: List[T]): List[Either[T, (Int, T)]] =
    encode(ls) map { e => if (e._1 == 1) Left(e._2) else Right(e) }

  ////////////////////////////////////////////////////////////////////////////////
  // P12 Decode a run-length encoded list
  def decode[T](ls: List[(Int, T)]): List[T] = ls flatMap {
    // pattern matching seems nicer than e => e._1, e._2
    case (n, x) => List.fill(n)(x)
    // or the deprecated version
    // List.make(n, x)
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P13 Run-length encoding of a list
  // same as P10

  ////////////////////////////////////////////////////////////////////////////////
  // P14 Duplicate the elements of a list
  def duplicate[A](ls: List[A]): List[A] = ls flatMap { e =>
    List(e, e)
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P15 Duplicate the elements of a list given a number of times
  def duplicateN[T](n: Int, ls: List[T]): List[T] = ls flatMap { e =>
    List.fill(n)(e)
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P16 Drop every Nth element of a list
  def drop[T](n: Int, ls: List[T]): List[T] = ls.grouped(n).toList.flatMap { l =>
    if (l.length == n) l.init
    else l
  }

  def dropRecursive[T](n: Int, ls: List[T]): List[T] = {
    def dropR(c: Int, ls: List[T]): List[T] = (c, ls) match {
      case (_, Nil) => Nil
      case (1, _ :: tail) => dropR(n, tail)
      case (_, h :: tail) => h :: dropR(c - 1, tail)
    }
    dropR(n, ls)
  }

  def dropTailRecursive[T](n: Int, ls: List[T]): List[T] = {
    def dropR(c: Int, result: List[T], curList: List[T]): List[T] = (c, curList) match {
      case (_, Nil) => result.reverse
      case (1, _ :: tail) => dropR(n, result, tail)
      case (_, h :: tail) => h :: dropR(c - 1, h :: result, tail)
    }
    dropR(n, Nil, ls)
  }

  // Functional 
  def dropFunctional[T](n: Int, ls: List[T]): List[T] = {
    ls.zipWithIndex.filter {
      case (x, ix) => (ix + 1) % n != 0
    }.map { _._1 }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P17 Split a list into two parts
  // need to handle out-of-bound argument
  def split[T](n: Int, ls: List[T]): (List[T], List[T]) = (n, ls) match {
    case (0, ls) => (Nil, ls)
    case (n, ls) if n < 0 || ls == Nil => (Nil, ls) // or throw new IllegalArgumentException
    case (n, h :: tail) => {
      val (prev, next) = split(n - 1, tail)
      (h :: prev, next)
    }
  }

  def splitTailRecursive[T](n: Int, ls: List[T]): (List[T], List[T]) = {
    def splitR(n: Int, result: List[T], curList: List[T]): (List[T], List[T]) = (n, curList) match {
      case (0, ls) => (result.reverse, ls)
      case (n, ls) if n < 0 || ls == Nil => (result.reverse, ls)
      case (n, h :: tail) => splitR(n - 1, h :: result, tail)
    }
    splitR(n, Nil, ls)
  }

  // Functional (barely not "builtin")
  def splitFunctional[T](n: Int, ls: List[T]): (List[T], List[T]) =
    (ls.take(n), ls.drop(n))

  ////////////////////////////////////////////////////////////////////////////////
  // P18 Extract a slice from a list
  // start counting the element with 0
  // [start, end)
  // need to consider when start or end <= 0
  def slice[T](start: Int, end: Int, ls: List[T]): List[T] =
    (start, end, ls) match {
      case (_, _, Nil) => Nil
      case (_, e, _) if e <= 0 => Nil
      case (s, e, h :: tail) if s <= 0 => h :: slice(0, e - 1, tail) // begin to take element
      case (s, e, h :: tail) => slice(s - 1, e - 1, tail)
    }

  def sliceTailRecursive[T](start: Int, end: Int, ls: List[T]): List[T] = {
    def sliceR(count: Int, result: List[T], curList: List[T]): List[T] =
      (count, curList) match {
        case (_, Nil) => result.reverse
        case (c, _) if end <= c => result.reverse
        case (c, h :: tail) if start <= c => sliceR(c + 1, h :: result, tail)
        case (c, h :: tail) => sliceR(c + 1, result, tail)
      }
    sliceR(0, Nil, ls)
  }

  def sliceFunctional[T](start: Int, end: Int, ls: List[T]): List[T] = ls.take(end).drop(start)

  ////////////////////////////////////////////////////////////////////////////////
  // P19 Rotate a list N places to the left
  // if N < 0, rotate right
  // what if N is very large?
  def rotate[T](n: Int, ls: List[T]): List[T] = {
    val nBounded = if (ls.isEmpty) 0 else n % ls.length
    if (nBounded < 0) rotate(nBounded + ls.length, ls)
    else (ls drop nBounded) ::: (ls take nBounded)
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P20 Remove the Kth element from a list
  def removeAt[T](n: Int, ls: List[T]): (List[T], T) = (n, ls) match {
    case (_, Nil) => throw new NoSuchElementException
    case (0, h :: tail) => (tail, h)
    case (n, h :: tail) => {
      val (ls, e) = removeAt(n - 1, tail)
      (h :: ls, e)
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P21 Insert an elemnt at a given position into a list
  def insertAt[T](e: T, n: Int, ls: List[T]): List[T] = ls.splitAt(n) match {
    case (pre, post) => pre ::: e :: post // what's the associativity?
  }
  // ls.take(n) ::: List(e) ::: ls.drop(n)

  ////////////////////////////////////////////////////////////////////////////////
  // P22 Create a list containing all integers within a given range
  def range(start: Int, end: Int): List[Int] =
    if (start > end) Nil
    else start :: range(start + 1, end)

  // Still not familiar about the following method
  // The classic functional approach would be to use `unfolder`, which Scala
  // doesn't have. So we'll write one and then use it.
  def unfoldRight[A, B](s: B)(f: B => Option[(A, B)]): List[A] =
    f(s) match {
      case None => Nil
      case Some((r, n)) => r :: unfoldRight(n)(f)
    }
  def rangeFunctional(start: Int, end: Int): List[Int] =
    unfoldRight(start) { n =>
      if (n > end) None
      else Some((n, n + 1))
    }

  ////////////////////////////////////////////////////////////////////////////////
  // P23 Extract a given number of randomly selected elements from a list
  def randomSelec1t[A](n: Int, ls: List[A]): List[A] =
    if (n <= 0) Nil
    else {
      val (rest, e) = removeAt((new util.Random).nextInt(ls.length), ls)
      e :: randomSelect(n - 1, rest)
    }

  // Create a uitl.Random once, since it's expensive
  def randomSelect[A](n: Int, ls: List[A]): List[A] = {
    def randomSelectR(n: Int, ls: List[A], r: util.Random): List[A] =
      if (n <= 0) Nil
      else {
        val (rest, e) = removeAt(r.nextInt(ls.length), ls)
        e :: randomSelectR(n - 1, ls, r)
      }
    randomSelectR(n, ls, new util.Random)
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P24 Lotto: Draw N different random numbers from the set 1..M
  // what if M is too large?
  def lotto(count: Int, max: Int): List[Int] =
    randomSelect(count, List.range(1, max + 1))

  ////////////////////////////////////////////////////////////////////////////////
  // P25 Generate a random permutation of the elements of a list
  // O(n^2)
  def randomPermutate1[A](ls: List[A]): List[A] = randomSelect(ls.length, ls)
  // The canonical way to shuffle imperatively is Fishser-Yates. It requires a
  // mutable array. This is O(n).
  // Still confused about how to use generic Array
  def randomPermutate[A: ClassManifest](ls: List[A]): List[A] = {
    val rand = new util.Random
    val a = ls.toArray
    for (i <- a.length - 1 to 1 by -1) {
      val ix = rand.nextInt(i + 1)
      val t = a(i)
      a.update(i, a(ix))
      a.update(ix, t)
    }
    a.toList
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P26 Generate the combinations of K distinct object chosen from the N elements of a list
  def combinations[A](k: Int, ls: List[A]): List[List[A]] = k match {
    case k if k < 0 => throw new IllegalArgumentException
    case 0 => List()
    case 1 => ls.map { List(_) }
    case _ => {
      List.range(0, ls.length - k + 1).flatMap { x =>
        val left = ls.drop(x)
        combinations(k - 1, left.tail).map { left.head :: _ }
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P27 Group the elements of a set into disjoint subsets
  def group[A](size: List[Int], ls: List[A]): List[List[List[A]]] = {
    if (size.sum != ls.size) {
      throw new IllegalArgumentException
    }
    size match {
      case Nil => List(Nil) // need to be contained in a List
      case k :: leftSize => combinations(k, ls).flatMap { x =>
        group(leftSize, ls.diff(x)).map { x :: _ }
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // P28 Sorting a list according to length of sublists
  def lsort[A](ls: List[List[A]]): List[List[A]] = ls.sortBy(_.length)
  def lsortFreq[A](ls: List[List[A]]): List[List[A]] = {
    /*
    val freq = collection.mutable.Map[Int, Int]()
    ls.foreach { x =>
      freq.update(x.length, freq.getOrElse(x.length, 0) + 1)
    }
    */
    val freq = Map(encode(ls.map(_.length).sorted).map(_.swap): _*)
    ls.sortBy(x => freq(x.length))
  }
}