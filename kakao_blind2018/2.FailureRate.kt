
fun solution(N: Int, stages: IntArray): IntArray {
    var answer = intArrayOf()
    val clearUserCnt = IntArray(N+2)
    val pendingUserCnt = IntArray(N+2)
    val failureRate = DoubleArray(N)

    for (stage in stages) {
        pendingUserCnt[stage] += 1
        for (i in 1..stage) {
            clearUserCnt[i] += 1
        }
    }

    for (i in 0 until N) {
        failureRate[i] = if (clearUserCnt[i+1] == 0) 0.0
                        else (pendingUserCnt[i+1].toDouble() / clearUserCnt[i+1])
    }
    answer = failureRate.withIndex().sortedByDescending { it.value }.map { it.index +1 }.toIntArray()
    return answer
}

fun main() {
    val a = solution(5, intArrayOf(2, 1, 2, 2, 2, 4, 3, 3))
    for (i in a) {
        print("$i, ")
    }
    println()

    val b = solution(4, intArrayOf(4,4, 4,4, 4))
    for (i in b) {
        print("$i, ")
    }
    println()


}


