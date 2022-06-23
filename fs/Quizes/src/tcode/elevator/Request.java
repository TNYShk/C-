package tcode.elevator;

public class Request implements Comparable<Request> {
    private InternalButton inRequest;
    private ExternalButton extRequest;

    public Request(InternalButton inButton, ExternalButton externalButton){
        inRequest = inButton;
        extRequest = externalButton;
    }

    public InternalButton getInternalRequest(){
        return inRequest;
    }
    public void setInternalRequest(InternalButton iButReq){
        this.inRequest = iButReq;
    }

    public ExternalButton getExtRequest(){
        return extRequest;
    }
    public void setExternalRequest(ExternalButton exBut){
        this.extRequest = exBut;
    }


    @Override
    public int compareTo(Request o) {
        if(this.getInternalRequest().getDestinationFloor() == o.getInternalRequest().getDestinationFloor())
            return 0;
        return (this.getInternalRequest().getDestinationFloor() > o.getInternalRequest().getDestinationFloor())? 1: -1;
    }
}
