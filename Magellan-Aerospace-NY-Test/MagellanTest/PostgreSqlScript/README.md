Put the PostgreSQL script of Part 1 here.

CREATE DATABASE Part

CREATE TABLE item (
    id INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (START WITH 1 INCREMENT BY 1) PRIMARY KEY,
    item_name varchar(250) NOT NULL,
    parent_item INTEGER REFERENCES item(id),
    cost INTEGER NOT NULL,
    req_date DATE NOT NULL
);

INSERT INTO item (item_name, parent_item, cost, req_date) VALUES
('Item1', null, 500, '2024-02-20'),
('Sub1', 1, 200, '2024-02-10'),
('Sub2', 1, 300, '2024-01-05'),
('Sub3', 2, 300, '2024-01-02'),
('Sub4', 2, 400, '2024-01-02'),
('Item2', null, 600, '2024-03-15'),
('Sub1', 6, 200, '2024-02-25');

SELECT * FROM item;

DROP FUNCTION Get_Total_cost;


CREATE OR REPLACE FUNCTION Get_Total_Cost(item_name_input VARCHAR)
RETURNS INTEGER AS $$
DECLARE
    total_cost INTEGER;
    parent INTEGER;
BEGIN
    select parent_item into parent
    from item
    where item_name = item_name_input;

    --RAISE NOTICE 'Value: %', parent;
    
    IF parent is not NULL THEN
        return NULL;
    ELSE
        WITH RECURSIVE ItemCTE AS (
            SELECT id, item_name, parent_item, cost
            FROM item
            WHERE item_name = item_name_input
            
            UNION ALL
            
            SELECT A.id, A.item_name, A.parent_item, A.cost
            FROM item as A
            INNER JOIN ItemCTE as B ON A.parent_item = B.id
        )
        SELECT SUM(cost) INTO total_cost
        FROM ItemCTE;
        
        RETURN total_cost;
    END if;
END;
$$ LANGUAGE plpgsql;


SELECT Get_Total_Cost('Item1') AS Total_Cost;
SELECT Get_Total_Cost('Sub1') AS Total_Cost;
SELECT Get_Total_Cost('Item2') AS Total_Cost;

SELECT *
FROM item