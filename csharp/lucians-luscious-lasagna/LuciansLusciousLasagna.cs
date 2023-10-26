class Lasagna
{
    public int ExpectedMinutesInOven(){
        return 40;
    }
    
    public int RemainingMinutesInOven(int actual_minutes){
        return ExpectedMinutesInOven() - actual_minutes;    
    }

    public int PreparationTimeInMinutes(int layers){
        return 2 * layers;
    }

    public int ElapsedTimeInMinutes(int layers, int actual_minutes){
        return PreparationTimeInMinutes(layers) + actual_minutes;
    }
}
