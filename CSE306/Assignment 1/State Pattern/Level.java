/**
 * @author Sahand Sabour 1614650
 */
package Assignment1_Part2;

public interface Level {
    public double getFees();
    public boolean canAccessPool();
    public boolean hasOwnLocker();
    public double getEquipmentDiscount();
    public FitnessCustomer getCustomer();
}
