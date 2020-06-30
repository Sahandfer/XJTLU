
public class Client {
    public static void main(String[] args) throws InterruptedException{
        ExpensiveObject object = new ExpensiveObjectProxy();
        System.out.println("Expensive Object Created!!!");
        Thread.sleep(3000);
        object.process();
        object.process();
    }
}