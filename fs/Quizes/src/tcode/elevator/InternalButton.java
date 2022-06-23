package tcode.elevator;

//client enters elevator and requests specific floor
public class InternalButton {
    private int destinationFloor;

    public InternalButton(int destinationFloor) {
        this.destinationFloor = destinationFloor;
    }
    public int getDestinationFloor() {
        return destinationFloor;
    }
    public void setDestinationFloor(int destinationFloor) {
        this.destinationFloor = destinationFloor;
    }

    @Override
    public String toString(){
        return " the destination floor: "+ destinationFloor;
    }

}
