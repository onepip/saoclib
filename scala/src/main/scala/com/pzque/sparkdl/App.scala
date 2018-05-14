import com.pzque.sparkdl.saoclib._

object App {
  def main(args: Array[String]): Unit = {
    test()
    testCL()
  }

  def test(): Unit = {
    System.loadLibrary("saoclib")
    val limits: Array[KernelArgLimit] = Array(
      limit(c_array(c_int, 10), mode_input),
      limit(c_array(c_int, 10), mode_input),
      limit(c_array(c_int, 10), mode_output)
    )

    val a = Array(1, 2, 3, 4, 5)
    val b = Array(1, 2, 3, 4, 5)
    val c = Array(1)
    val values = Array(
      ArgIntArray(a, 5, mode_input),
      ArgIntArray(b, 5, mode_input),
      ArgIntArray(c, 5, mode_output)
    )

    limits.zip(values).foreach(
      x => {
        val limit = x._1
        val value = x._2
        limit.verify(value)
      }
    )
  }


  def testCL() = {
    System.loadLibrary("saoclib")

    val env = new ClEnv()
    env.initOpenCL()
    val image = new ClImage(env.getNativeHandler, "/home/pcz/Projects/saoclib/bin/matrix_mult")
    val device = env.getDeviceId(0).get
    val devices = Array(device)
    image.deployImage(devices)
  }


}