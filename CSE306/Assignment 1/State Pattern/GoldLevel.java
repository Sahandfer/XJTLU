/**
 * @author Sahand Sabour 1614650
 */
package Assignment1_Part2;

public class GoldLevel implements Level {

    private final double FEE = 2000;
    private final double DISCOUNT = 200;
    private FitnessCustomer customer;

    public GoldLevel(Level level) {
        this(level.getCustomer());
    }

    public GoldLevel(FitnessCustomer customer) {
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
        return true;
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
