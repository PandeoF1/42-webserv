<?php
echo ("POST : ");
print_r ($_POST);
echo ("<br>GET : ");
print_r ($_GET);
echo ("<br>");
echo ($_POST["a"]);
echo ("<br>");
echo ($_POST["b"]);
echo ("<br>");
echo ($_POST["c"]);
echo ("<br>");
?>
Post : <br>
<form action="test.php" method="post">
  <div>
    <label for="say">a</label>
    <input name="say" id="say" value="a">
  </div>
  <div>
    <label for="to">b</label>
    <input name="to" value="b">
  </div>
  <div>
    <button>Send</button>
  </div>
</form>
Get : <br>
<form action="test.php" method="get">
  <div>
    <label for="say">a</label>
    <input name="say" id="say" value="a">
  </div>
  <div>
    <label for="to">b</label>
    <input name="to" value="b">
  </div>
  <div>
    <button>Send</button>
  </div>
</form>
:)
<br>
123456