/**
 * @author Sahand Sabour 1614650
 */
package Assignment1_Part2;

public class FitnessCustomer {

    private Level level;

    public void setLevel(Level level) {
        this.level = level;
    }

    public double getFees() {
        return level.getFees();
    }

    public boolean canAccessPool() {
        return level.canAccessPool();
    }

    public boolean hasOwnLocker() {
        return level.hasOwnLocker();
    }

    public double getEquipmentDiscount() {
        return level.getEquipmentDiscount();
    }
}
