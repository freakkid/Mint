/* 
 * A spiralBug runs by spiral pattern
 * @datetime 2017-03-25
 */

import info.gridworld.actor.Bug;

/**
 * A <code>SpiralBug</code> traces out a spiral of a given size. <br />
 * The implementation of this class is testable on the AP CS A and AB exams.
 */
public class SpiralBug extends Bug
{
    private int steps;
    private int sideLength;

    /**
     * Constructs a spiral bug that traces a spiral of a given side length
     * @param length the side length
     */
    public SpiralBug(int length)
    {
        steps = 0;
        sideLength = length;
    }

    /**
     * Moves to the next location of the square.
     */
    public void act()
    {
        if (steps < sideLength && canMove())
        {
            move();
            steps++;
        }
        else if (steps == sideLength && canMove()) {
            turnTwice();
            sideLength += 1;
        }
        else
        {
            turnTwice();
        }
    }

    private void turnTwice() {
        turn();
        turn();
        steps = 0;
    }
}