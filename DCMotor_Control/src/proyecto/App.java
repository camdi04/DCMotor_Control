/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyecto;

import java.awt.Color;
import static java.lang.System.exit;
import java.net.InterfaceAddress;
import javax.swing.JOptionPane;

/**
 *
 * @author Saray
 */
public class App {
    public static void main(String args[]) {
        int resp = JOptionPane.showConfirmDialog(null, "¿Desea utilizar el programa?", "Alerta!", JOptionPane.YES_NO_OPTION);
        if(resp == 1){
            exit(1);
        } else{
        
        Principal principal= new Principal();
        principal.setVisible(true);
        }
    }
}
