package tcode.elevator;

import java.util.TreeSet;

public class Elevator {
    private int currentFloor = 0;
    private Direction currentDir = Direction.UP;
    private State curState = State.IDLE;


    private TreeSet<Request> currentJobs = new TreeSet<>();
    private TreeSet<Request> upPendings = new TreeSet<>();
    private TreeSet<Request> downPendings = new TreeSet<>();

    public void startElevator(){
        while(true) {
            if (checkforjob()) {
                if (currentDir == Direction.UP) {
                    Request request = currentJobs.pollFirst();
                    processUpRequest(request);
                    if (currentJobs.isEmpty()) {
                        addPendingDownJobs();
                    }
                }
                if (currentDir == Direction.DOWN) {
                    Request request = currentJobs.pollLast();
                    processUpRequest(request);
                    if (currentJobs.isEmpty()) {
                        addPendingUpJobs();
                    }

                }
            }

        }
    }
    public boolean checkforjob(){
        return !currentJobs.isEmpty();
    }

    private void processUpRequest(Request req){
        int startingFloor = currentFloor;
        int requestedFloor = req.getExtRequest().getCurrentFloor();
        if(startingFloor <  requestedFloor){
            for(int i = startingFloor; i<=requestedFloor; ++i){
                try{
                    Thread.sleep(1000);
                } catch (InterruptedException e){
                    e.printStackTrace();
                }
                System.out.println("arrived at destination floor! "+i);
            currentFloor = i;
            }
        }
        System.out.println("reached source floor, doors are opening");
        startingFloor = currentFloor;
        int intReq = req.getInternalRequest().getDestinationFloor();

        for(int i= startingFloor; i<=intReq;++i){
            try{
                Thread.sleep(1000);
            } catch (InterruptedException e){
                e.printStackTrace();
            }
            System.out.println("reached floor "+i);
            currentFloor = i;
            if(checkForNewJobstoProcess(req)){
                break;
            }
        }
    }
    private boolean checkForNewJobstoProcess(Request curReq){
        System.out.println("check for new jobs to process");
        if(checkforjob()){
            if(currentDir == Direction.UP){
                Request request = currentJobs.pollFirst();
                int inReq = request.getInternalRequest().getDestinationFloor();
                if(inReq < curReq.getInternalRequest().getDestinationFloor()){
                    currentJobs.add(request);
                    currentJobs.add(curReq);
                    return true;
                }
                currentJobs.add(request);
            }
            if(currentDir == Direction.DOWN){
                Request req = currentJobs.pollLast();
                int inReq = req.getInternalRequest().getDestinationFloor();
                if(inReq > curReq.getInternalRequest().getDestinationFloor()){
                    currentJobs.add(req);
                    currentJobs.add(curReq);
                    return true;
                }
                currentJobs.add(req);
            }
        }
        return false;
    }
    private void addPendingDownJobs(){
        if(!downPendings.isEmpty()){
            currentJobs = downPendings;
            currentDir = Direction.DOWN;
            curState = State.MOVING;
        }else{
            curState = State.IDLE;
            System.out.println("IDLE elevator");
        }
    }

    private void addPendingUpJobs(){
        if(!upPendings.isEmpty()){
            currentJobs = upPendings;
            currentDir = Direction.UP;
            curState = State.MOVING;
        }else{
            curState = State.IDLE;
            System.out.println("IDLE elevator");
        }
    }

    public void addJob(Request request){
        if(curState == State.IDLE){
            curState = State.MOVING;
            currentDir = request.getExtRequest().getDirectionTo();
            currentJobs.add(request);
        }else if(curState == State.MOVING){
            if(request.getExtRequest().getDirectionTo() != currentDir){
                if(currentDir == Direction.UP && request.getInternalRequest().getDestinationFloor() < currentFloor){
                    addToPendingJobs(request);
                }else if(currentDir == Direction.DOWN && request.getInternalRequest().getDestinationFloor() > currentFloor){
                    addToPendingJobs(request);
                }else{
                    currentJobs.add(request);
                }
            }
        }
        System.out.println("add job");
    }
    public void addToPendingJobs(Request request){
        if(request.getExtRequest().getDirectionTo() == Direction.UP){
            System.out.println("add to UP pending jobs");
            upPendings.add(request);
        }else{
            System.out.println("add to DOWN pending jobs");
            downPendings.add(request);
        }
    }
}
class ProcessJobWorker implements Runnable{
    private Elevator elevator;

    ProcessJobWorker(Elevator ele){
        this.elevator = ele;
    }
    @Override
    public void run() {
        elevator.startElevator();
    }
}

enum State{ MOVING, STOP, IDLE}

class AddJobWorker implements Runnable{
    private Elevator elevator;
    private Request request;

    public AddJobWorker(Elevator elevator,Request request){
        this.elevator = elevator;
        this.request = request;
    }
    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName() + " class addjobworker");
        try{
            Thread.sleep(200);
        }catch (InterruptedException e){
            e.printStackTrace();
        }
        elevator.addJob(request);
    }
}
