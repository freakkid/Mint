
package info.gridworld.maze;

import info.gridworld.actor.Actor;
import info.gridworld.actor.Bug;
import info.gridworld.actor.Flower;
import info.gridworld.actor.Rock;
import info.gridworld.grid.*;

import java.awt.Color;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
import java.util.Stack;

import javax.swing.JOptionPane;



/**
 * A <code>MazeBug</code> can find its way in a maze. <br />
 * The implementation of this class is testable on the AP CS A and AB exams.
 */
public class MazeBug extends Bug {

    private Location next = null;
    private Location last = null;
    private boolean isEnd = false;
    private Stack<ArrayList<Location>> crossLocation = new Stack<ArrayList<Location>>();
    private Integer stepCount = 0;
    // final message has been shown
    private boolean hasShown = false;
    private Set<Location> visitedLocations = new HashSet<Location>();
    private int[] directions = {10, 10, 10, 10};

    /**
     * Constructs a maze bug
     * 
     * @param none
     * 
     */
    public MazeBug() {
        setColor(Color.GREEN);
        last = null;
    }

    /**
     * Moves to the next location of the square.
     */
    public void act() {
        boolean willMove = canMove();
        if (isEnd) {
            // to show step count when reach the goal
            if (!hasShown) {
                String msg = stepCount.toString() + " steps";
                JOptionPane.showMessageDialog(null, msg);
                hasShown = true;
            }
        } else if (willMove) {
            move();
            // increase step count when move
            stepCount++;
        }
    }

    /**
     * Find all positions that can be move to.
     * 
     * @param loc
     *            the location to detect.
     * @return List of positions.
     */
    public ArrayList<Location> getValid(Location loc) {
        Grid<Actor> gr = getGrid();
        if (gr == null) {
            return null;
        }
        ArrayList<Location> valid = new ArrayList<Location>();
        for (Actor actor : gr.getNeighbors(getLocation())) {
            int row = actor.getLocation().getRow();
            int col = actor.getLocation().getCol();
            // 获取上下左右四个方向的location上的actor
            if (row == getLocation().getRow() || col == getLocation().getCol()) {
            	// 红石头v
                if ((actor instanceof Rock) && actor.getColor().equals(Color.RED))
                {
                    isEnd = true;
                }
                // 花可以直接当成空白的位置
                else if (actor instanceof Flower)
                {
                	valid.add(actor.getLocation());
                }
            }
        }
        // 再获得上下左右四个方向的空位置
        for (Location emptyLocation : gr.getEmptyAdjacentLocations(loc)) {
            int row = emptyLocation.getRow();
            int col = emptyLocation.getCol();
            if (row == getLocation().getRow() || col == getLocation().getCol()) {
                valid.add(emptyLocation);
            }
        }
        return valid;
    }

    /**
     * Tests whether this bug can move forward into a location that is empty or
     * contains a flower.
     * 
     * @return if this bug can move.
     */

    public boolean canMove() {
        Grid<Actor> gr = getGrid();
        if (gr == null) {
            return false;
        }
        Location loc = getLocation();
        ArrayList<Location> allValidLocations = getValid(loc);
        ArrayList<Location> validLocations = new ArrayList<Location>();
        // 判断已经获得的allValidLocations是否已经走过，取出不曾走过的location
        if (visitedLocations.size() != 0) {
            for (Location allValidLocation : allValidLocations) {
            	boolean isVisited = false;
                for (Location visitedLocation : visitedLocations) {
                    if (allValidLocation.equals(visitedLocation)) {
                        isVisited = true;
                    }
                }
                if (!isVisited) {
                    validLocations.add(allValidLocation);
                }
                
            }
        }
        else {
            validLocations = allValidLocations;
        }
        // 如果有未走过的location
        if (validLocations.size() > 0) {
        	// 随机取一个位置
            // next = validLocations.get((int)(Math.random() * 10) % validLocations.size());
        	next = getNextLocation(validLocations);
            // 把当前位置压入，即当前位置是最后一个元素
            validLocations.add(getLocation());
            crossLocation.push(validLocations);

        }// 全都走过，则往回走
        else {
            // 取出之前走过的节点
        	validLocations = crossLocation.pop();
        	// 取出之前走过的位置
            next = validLocations.get(validLocations.size() - 1);
            // 回走的时候概率要减少
            if (next.getDirectionToward(getLocation()) == Location.SOUTH) {
                directions[0]--;
            }
            if (next.getDirectionToward(getLocation()) == Location.NORTH) {
                directions[1]--;
            }
            if (next.getDirectionToward(getLocation()) == Location.WEST) {
                directions[2]--;
            }
            if (next.getDirectionToward(getLocation()) == Location.EAST) {
                directions[3]--;
            }
        }
        return true;
    }

    private Location getNextLocation(ArrayList<Location> validLocations) {
    	Location[] validloc = new Location[4];
        for (Location validLocation : validLocations) {
            if (validLocation.getDirectionToward(getLocation()) == Location.SOUTH) {
                validloc[0] = validLocation;
            }
            if (validLocation.getDirectionToward(getLocation()) == Location.NORTH) {
                validloc[1] = validLocation;
            }
            if (validLocation.getDirectionToward(getLocation()) == Location.WEST) {
                validloc[2] = validLocation;
            }
            if (validLocation.getDirectionToward(getLocation()) == Location.EAST) {
                validloc[3] = validLocation;
            }
        }

        int maxIndex = -1;
        // 获得最大数字的下标志
        for (int i = 0; i < validloc.length; i++) {
            if (validloc[i] != null) {
                if (maxIndex == -1) {
                	maxIndex = i;
                }
                if (directions[maxIndex] < directions[i]) {
                	maxIndex = i;

                }
            }

        }
        directions[maxIndex]++;
        return validloc[maxIndex];
	}
    /**
     * Moves the bug forward, putting a flower into the location it previously
     * occupied.
     */
    public void move() {
        Grid<Actor> gr = getGrid();
        if (gr == null) {
            return;
        }
        Location loc = getLocation();
        if (gr.isValid(next)) {
            setDirection(getLocation().getDirectionToward(next));
            last = getLocation();
            
            visitedLocations.add(last);
            moveTo(next);
        } else {
            removeSelfFromGrid();
        }
        Flower flower = new Flower(getColor());
        flower.putSelfInGrid(gr, loc);
    }
}
