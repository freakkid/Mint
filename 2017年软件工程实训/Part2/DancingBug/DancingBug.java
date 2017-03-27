/* 
 * A bug can turn according an int array.
 * @datetime 2017-03-25
 */

import info.gridworld.actor.Bug;
import java.lang.System;

/**
 * A <code>DancingBug</code> traces out a square "box" of a given size. <br />
 * The implementation of this class is testable on the AP CS A and AB exams.
 */
public class DancingBug extends Bug
{
    private int[] turnArray;
    private int turnArrayLength;
    private int currentArrayEntry;
    private int turnCount;
    /**
     * Constructs a dancing bug that turns before move once and
     * the times of turning depending the turnrray
     * @param the list of the turn times 
     */
    public DancingBug(int[] array)
    {
        initTurnArray(array);
        currentArrayEntry = 0;
        turnCount = 0;
    }

    // copy the list of the turning times 
    private void initTurnArray(int[] array)
    {
        turnArrayLength = array.length;
        turnArray = new int[turnArrayLength];
        System.arraycopy(array, 0, turnArray, 0, turnArrayLength);
    }

    /**
     * Moves to the next location before turning.
     */
    public void act()
    {
        if (turnCount < turnArray[currentArrayEntry]) 
        {
            turnCount++;
            turn();
        }
        else if (turnCount == turnArray[currentArrayEntry]) {
            turnCount = 0;
            currentArrayEntry = (currentArrayEntry + 1) % turnArrayLength;
            if (canMove())
            {
                move();
            }
        }
    }


}