import info.gridworld.grid.AbstractGrid;
import info.gridworld.grid.Location;
import info.gridworld.actor.Actor;
import java.util.*;
import java.util.ArrayList;

public class SparseBoundedGrid2<E> extends AbstractGrid<E>
{
	// copy the code from UnbounfgGrid fom gridworld <the official version>
    // using map to implement the boundgrid
    private Map<Location, E> occupantMap;
	private int rows;
	private int cols;

	public SparseBoundedGrid2(int row, int col)
	{
		if (row <= 0) {
			throw new IllegalArgumentException("rows <= 0");
        }
		if (col <= 0) {
			throw new IllegalArgumentException("cols <= 0");
        }
		rows = row;
		cols = col;
		occupantMap = new HashMap<Location, E>();
	}

	public int getNumRows()
    {
        return rows;
    }

    public int getNumCols()
    {
        return cols;
    }
    // if not overflow
    public boolean isValid(Location loc)
    {
        return 0 <= loc.getRow() && loc.getRow() < getNumRows()
                && 0 <= loc.getCol() && loc.getCol() < getNumCols();
    }

    public ArrayList<Location> getOccupiedLocations()
    {
        ArrayList<Location> a = new ArrayList<Location>();
        for (Location loc : occupantMap.keySet())
            a.add(loc);
        return a;
    }

    public E get(Location loc)
    {
    	if (!isValid(loc)) {
            throw new IllegalArgumentException("Location " + loc
                    + " is not valid");
        }

        return occupantMap.get(loc);
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
        return occupantMap.put(loc, obj);
    }

    public E remove(Location loc)
    {
        if (!isValid(loc)) {
            throw new IllegalArgumentException("Location " + loc
                    + " is not valid");
        }
        return occupantMap.remove(loc);
    }


}