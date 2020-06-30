/**
 * @author Sahand Sabour 1614650
 */
package Assignment1_Part2;

public class Assignment1_Part2 {
    public static void main(String[] args) {
        FitnessCustomer Sahand = new FitnessCustomer();
        Sahand.setLevel(new GoldLevel(Sahand));

        System.out.println("Fee: "+ Sahand.getFees()+"\tDiscount: "+Sahand.getEquipmentDiscount());
        System.out.println((Sahand.canAccessPool()?"Has":"No")+" Pool Access");
        System.out.println((Sahand.hasOwnLocker()?"Has":"No")+" Own Locker");
        System.out.println();
        
        Sahand.setLevel(new SilverLevel(Sahand));

        System.out.println("Fee: "+ Sahand.getFees()+"\tDiscount: "+Sahand.getEquipmentDiscount());
        System.out.println((Sahand.canAccessPool()?"Has":"No")+" Pool Access");
        System.out.println((Sahand.hasOwnLocker()?"Has":"No")+" Own Locker");
        System.out.println();
        
        Sahand.setLevel(new BronzeLevel(Sahand));

        System.out.println("Fee: "+ Sahand.getFees()+"\tDiscount: "+Sahand.getEquipmentDiscount());
        System.out.println((Sahand.canAccessPool()?"Has":"No")+" Pool Access");
        System.out.println((Sahand.hasOwnLocker()?"Has":"No")+" Own Locker");
        System.out.println();
    }
}
