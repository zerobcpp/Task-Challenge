using Microsoft.AspNetCore.Mvc;
using Npgsql;
using System.Text.Json;

namespace MagellanTest.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class ItemsController : ControllerBase
    {

        private readonly string _conn = ""; //

        [HttpPost]
        public IActionResult CreateItem([FromBody] JsonElement requestBody)
        {
            try
            {
                using var connection = new NpgsqlConnection(_conn);
                connection.Open();

                var itemName = requestBody.GetProperty("item_name").GetString();
                var parentItem = requestBody.GetProperty("parent_item").GetInt32();
                var cost = requestBody.GetProperty("cost").GetInt32();
                var reqDate = DateTime.Parse(requestBody.GetProperty("req_date").GetString());

                using var cmd = new NpgsqlCommand("INSERT INTO item (item_name, parent_item, cost, req_date) VALUES (@itemName, @parentItem, @cost, @reqDate) RETURNING id", connection);
                cmd.Parameters.AddWithValue("@itemName", itemName);
                cmd.Parameters.AddWithValue("@parentItem", parentItem);
                cmd.Parameters.AddWithValue("@cost", cost);
                cmd.Parameters.AddWithValue("@reqDate", reqDate);

                var id = (int)cmd.ExecuteScalar();
                return Ok(id.ToString());
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }
        [HttpGet("{id}")]
        public IActionResult GetItem(int id)
        {
            try
            {
                using var connection = new NpgsqlConnection(_conn);
                connection.Open();

                using var cmd = new NpgsqlCommand("SELECT * FROM item WHERE id = @id", connection);
                cmd.Parameters.AddWithValue("@id", id);
                using var reader = cmd.ExecuteReader();

                if (reader.Read())
                {
                    var item = new
                    {
                        id = reader.GetInt32(0),
                        item_name = reader.GetString(1),
                        parent_item = reader.IsDBNull(2) ? null : (int?)reader.GetInt32(2),
                        cost = reader.GetInt32(3),
                        req_date = reader.GetDateTime(4)
                    };
                    return Ok(item);
                }
                else
                {
                    return NotFound();
                }
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        [HttpGet("totalcost/{item_name}")]
        public IActionResult GetTotalCost(string item_name)
        {
            try
            {
                using var connection = new NpgsqlConnection(_conn);
                connection.Open();

                // Call Get_Total_Cost function
                using var cmd = new NpgsqlCommand("SELECT Get_Total_Cost(@itemName)", connection);
                cmd.Parameters.AddWithValue("@itemName", item_name);
                var totalCost = (int)cmd.ExecuteScalar();
                return Ok(new { totalCost });
            }
            catch (Exception ex)
            {
                return BadRequest("requested item is not a parent item.");
            }
        }
    }
}