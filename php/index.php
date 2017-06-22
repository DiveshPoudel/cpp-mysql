 <?php
	require 'classes/Database.php';
	
	$database = new Database;

//	inserting data
	$post = filter_input_array(INPUT_POST, FILTER_SANITIZE_STRING);
	if($_POST['submit']){
		$title = $_POST['title'];
		$body = $post['body'];
		
		$database->query('INSERT INTO posts(title,body) VALUES(:title,:body)');
		$database->bind(':title',$title);
		$database->bind(':body',$body);
		$database->execute();
		if($database->lastInsertId()){
			echo '<p>Post Added!</p>';
		}
	}
	
// fetching data	
	$database->query('SELECT * FROM post');
	$rows = $database->resultset();
?>

	<h1>Add Post</h1>
	<form method="post" action="<?php /*inserting data in form*/ $_SERVER['PHP_SELF']?>">
		<label>Post ID</label><br/>
		<input type="text" name="title" placeholder="Add a Title"/><br/>
		<label>Post body</label><br/>
		<textarea name="body"></textarea>
		<input type="submit" name="submit" value="Submit" />
	</form>
<h1>Posts</h1>
<div>
<?php /*displaying data*/ foreach($rows as $row): ?>
	<div>
		<h3><?php echo $row['title'];?></h3>
		<p><?php echo $row['body'];?></p>
	</div>
<?php endforeach;?>
</div>