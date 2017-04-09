import info.gridworld.grid.AbstractGrid;
import info.gridworld.grid.Location;
import info.gridworld.actor.Actor;
import java.util.*;


public class UnboundedGrid2<E> extends AbstractGrid<E>
{
    // copy the code from BounfgGrid fom gridworld <the official version>
    // using array to implement unboundgrid
	private Object[][] occupantArray;

	public UnboundedGrid2()
	{
        occupantArray = new Object[16][16];
	}

    // get the lenght of occupantArray
	private int getOccupantArrayLength()
	{
		return occupantArray.length;
	}

    public int getNumRows()
    {
        return -1;
    }

    public int getNumCols()
    {
        return -1;
    }

	private void resizeOccupantArray(Location loc)
	{
		int size = getOccupantArrayLength();
        // copy the old array
		Object[][] oldOccupantArray = new Object[size][size]; 
        for (int i = 0; i < size; i++)
        {
            oldOccupantArray[i] = occupantArray[i].clone();
        }
        // get the new size that large enough
        int newSize = size * 2;
        int minSize = loc.getCol() > loc.getRow() ? loc.getCol() : loc.getRow();
        while (newSize - 1 < minSize)
        {
            newSize *= 2;
        }
        // get a new lager array
        occupantArray = new Object[newSize][newSize];
        // copy the old array
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++) {
                occupantArray[i][j] = oldOccupantArray[i][j];
            }
        }
	}
    // check if row and col is >= 0
	public boolean isValid(Location loc)
	{
		return loc.getRow() >= 0 && loc.getCol() >= 0;
	}
    // check if need to resize the Array
    // if the loction is overflow
	public boolean isNeedResize(Location loc)
	{
		return loc.getCol() > getOccupantArrayLength() - 1 || loc.getRow() > getOccupantArrayLength() - 1;
	}

    public ArrayList<Location> getOccupiedLocations()
    {
        ArrayList<Location> theLocations = new ArrayList<Location>();

        int size = getOccupantArrayLength();
        for (int r = 0; r < size; r++)
        {
            for (int c = 0; c < size; c++)
            {
                Location loc = new Location(r, c);
                if (get(loc) != null)
                    theLocations.add(loc);
            }
        }

        return theLocations;
    }

    @SuppressWarnings("unchecked")
    public E get(Location loc)
    {
    	if (!isValid(loc)) {
            throw new IllegalArgumentException("Location " + loc
                    + " is not valid");
        }
        if (isNeedResize(loc)) {
            resizeOccupantArray(loc);
        }
        return (E) occupantArray[loc.getRow()][loc.getCol()];
    }


    public E put(Location loc, E obj)
    {
        if (!isValid(loc)) {
            throw new IllegalArgumentException("Location " + loc
                    + " is not valid");
        }
        if (obj == null) {
            throw new NullPointerException("obj == null");
        }

        E oldOccupant = get(loc);

        occupantArray[loc.getRow()][loc.getCol()] = obj;
        return oldOccupant;
    }

    public E remove(Location loc)
    {
        if (!isValid(loc)) {
            throw new IllegalArgumentException("Location " + loc
                    + " is not valid");
        }
        
        E r = get(loc);
        occupantArray[loc.getRow()][loc.getCol()] = null;
        return r;
    }

}