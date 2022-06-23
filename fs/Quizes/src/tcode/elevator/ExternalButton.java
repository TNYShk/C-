package tcode.elevator;

//class for client wanting to call the elevator
public class ExternalButton {
        private int currentFloor;
        private Direction whereTo;

        public ExternalButton(Direction where, int sourceFloor){
                currentFloor = sourceFloor;
                whereTo = where;
        }

        public Direction getDirectionTo(){
                return whereTo;
        }
        public void setDirectionTo(Direction where){
                whereTo = where;
        }

        public void setSourceFloor(int current){
                currentFloor = current;
        }

        public int getCurrentFloor(){
                return currentFloor;
        }

        @Override
        public String toString(){
                return " The elevator has been called from floor: "+ currentFloor+ " and will go " +whereTo;
        }
}
