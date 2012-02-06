<?
/**
 * @name         Snapshot
 * @version      12
 * @package      snap
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0206
 */


// cron job task for for automating snapshots

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";
require("../../conf/sahana.conf");
require("./conf.inc");
require('class.SQLBackup.php');

$db_host = $conf['db_host'].":".$conf['db_port'];
$db_name = $conf['db_name'];
$db_user = $conf['db_user'];
$db_pass = $conf['db_pass'];
$dir     = $conf['mod_snap_storage_location'];

// add a trailing slash to the storage location in case someone forgot to put it there in the conf :D
if (substr($dir, -1) != "/") {
	$dir .= "/";
}
$outputFile = $dir.$db_name."@".date("Ymd")."_".date("Gis").".sql";

//---- FALSE == tables' structure and all their data (everything) will be stored // TRUE == only tables' structure will be stored.
$structure_only = FALSE;

//---- instantiating object
$backup = new SQLBackup($db_user, $db_pass, $db_name, $db_host, $outputFile, $structure_only);

//---- calling the backup method finally creates a sqldump into a file with the name specified in $outputFile
$backup->backup();

//---- log details
echo "Snapshot created: ".$db_name."@".date("Ymd")."_".date("Gis").".sql\n";
