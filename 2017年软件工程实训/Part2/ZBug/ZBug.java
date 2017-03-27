/* 
 * A circleBug runs by "Z" pattern
 * @datetime 2017-03-25
 */

import info.gridworld.actor.Bug;
import info.gridworld.grid.Location;

/**
 * A <code>ZBug</code> traces out a like "Z" of a given size. <br />
 * The implementation of this class is testable on the AP CS A and AB exams.
 */


public class ZBug extends Bug
{
    private int steps;
    private int sideLength;
    private int turnCount;
    private int currentTurnTimesEntry;
    private final int turnTimes[] = {3, 5};
    /**
     * Constructs a box bug that traces a like "Z" of a given side length
     * @param length the side length
     */
    public ZBug(int length)
    {
        steps = 0;
        sideLength = length;
        turnCount = 0;
        currentTurnTimesEntry = 0;
        setDirection(Location.RIGHT);
    }

    /**
     * Moves to the next location of the Z.
     */
    public void act() 
    {
        if (canMove() && currentTurnTimesEntry <= turnTimes.length)
        {
            if (steps < sideLength)
            {
                steps++;
                move();
            }
            else if (steps == sideLength && currentTurnTimesEntry < turnTimes.length)
            {
                if (turnCount < turnTimes[currentTurnTimesEntry])
                {
                    turn();
                    turnCount++;
                }
                if (turnCount == turnTimes[currentTurnTimesEntry])
                {
                    turnCount = 0;
                    steps = 0;
                    currentTurnTimesEntry++;
                }
            }

        }
    }

}