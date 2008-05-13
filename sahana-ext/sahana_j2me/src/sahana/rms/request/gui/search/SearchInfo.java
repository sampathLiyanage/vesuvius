/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  SearchInfo.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.search;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

/* Authors : Kasun T Karunanayake
 */

public class SearchInfo implements CommandListener {

    private Display display;
    private Form form;
    private Form backscreen;
    private Command next;
    private Command back;
    private String info;

    public SearchInfo(Display dis , String info , Form frm) {

        backscreen = frm;
        display = dis;
        this.info = info;
        form  = new Form("Request Information");
        String ide = new String(info);
        form.append(ide);

        next  = new Command("Ok" , Command.OK , 1);
        back  = new Command("Back" , Command.BACK , 2);

        form.addCommand(next);
        form.addCommand(back);
        form.setCommandListener(this);

        display.setCurrent(form);
    }

    public void commandAction(Command command , Displayable displayable) {
        if (command == next) {
            /*NewItem ni = new NewItem(display);*/
        } else if (command == back) {
            display.setCurrent(backscreen);
            /*display.setCurrent(backscreen);*/
        }
    }
}