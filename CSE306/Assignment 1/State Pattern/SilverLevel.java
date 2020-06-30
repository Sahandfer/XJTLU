/**
 * @author Sahand Sabour 1614650
 */
package Assignment1_Part2;

public class SilverLevel implements Level {

    private final double FEE = 1500;
    private final double DISCOUNT = 100;
    private FitnessCustomer customer;

    public SilverLevel(Level level) {
        this(level.getCustomer());
    }
    public SilverLevel(FitnessCustomer customer) {
        this.customer = customer;
    }
    @Override
    public double getFees() {
        return FEE;
    }
    @Override
    public boolean canAccessPool() {
        return true;
    }
    @Override
    public boolean hasOwnLocker() {
        return false;
    }
    @Override
    public double getEquipmentDiscount() {
        return DISCOUNT;
    }
    @Override
    public FitnessCustomer getCustomer() {
        return customer;
    }
}