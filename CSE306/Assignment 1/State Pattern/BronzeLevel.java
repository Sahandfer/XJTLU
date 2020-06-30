/**
 * @author Sahand Sabour 1614650
 */
package Assignment1_Part2;

public class BronzeLevel implements Level {

    private final double FEE = 1000;
    private final double DISCOUNT = 50;
    private FitnessCustomer customer;

    public BronzeLevel(Level level) {
        this(level.getCustomer());
    }
    public BronzeLevel(FitnessCustomer customer) {
        this.customer = customer;
    }
    @Override
    public double getFees() {
        return FEE;
    }
    @Override
    public boolean canAccessPool() {
        return false;
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