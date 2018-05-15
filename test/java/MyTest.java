class MyTest
{
  private static int magic_counter = 0;

  private int uid;

  public MyTest()
  {
    uid = magic_counter++ * 2;
  }

  public void showId()
  {
    System.out.println(uid);
  }
}
