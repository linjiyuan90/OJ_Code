package Arthmetic {

  class S99Int(val start: Int) {

    import S99Int._

    ////////////////////////////////////////////////////////////////////////////////
    // P31 Determine whether a given integer number is prime
    //
    // A fairly naive implemention for primarity testing is simply:
    // a number is prime if it's not divisible by any prime number less than or equal
    // to its square root
    // Here, we use a Stream to create a lazy infinite list for prime numbers. 
    // the mutual recursion between `primes` and `isPrime` works because of the limit on
    // `isPrime` to the square root of the number being tested.
    def isPrime: Boolean = {
      (start > 1) && (primes takeWhile { _ <= Math.sqrt(start) } forall { start % _ != 0 })
    }

    ////////////////////////////////////////////////////////////////////////////////
    // P33 Determine whether two positive integer number are coprime
    def isCoprimeTo(n: Int): Boolean = gcd(start, n) == 1

    ////////////////////////////////////////////////////////////////////////////////
    // P34 Calculate Euler's totient function phi(m)
    // Euler's so-called totient function phi(m) is defined as the numebr of positive
    // integers r (1 <= r < m) that are coprime to m. As a special case, phi(1) is 
    // defined to be 1
    def totient = (1 to start) filter { start.isCoprimeTo(_) } length

    ////////////////////////////////////////////////////////////////////////////////
    // P35 Determine the prime factors of a given positive integer
    // > 315.primeFactors
    // List(3, 3, 5, 7)
    def primeFactors = {
      // they should share the same Stream object
      def primeFactorsR(n: Int, ps: Stream[Int]): List[Int] =
        if (n.isPrime) List(n)
        else if (n % ps.head == 0) ps.head :: primeFactorsR(n / ps.head, ps)
        else primeFactorsR(n, ps.tail)
      primeFactorsR(start, primes)
    }
    // primes takeWhile { _ <= Math.sqrt(start) } filter { start % _ == 0 } toList
    // need factors, not unique factors

    ////////////////////////////////////////////////////////////////////////////////
    // P36
  }

  object S99Int {
    implicit def int2S99Int(i: Int): S99Int = new S99Int(i)

    val primes = Stream.cons(2, Stream.from(3, 2).filter { _.isPrime })

    ////////////////////////////////////////////////////////////////////////////////
    // P32 Determine the greatest common divisor of two positive integer
    def gcd(n: Int, m: Int): Int = if (m == 0) n else gcd(m, n % m)

  }
}