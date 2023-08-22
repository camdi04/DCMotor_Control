/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyecto;

import com.google.gson.Gson;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.Buffer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Saray
 */
public class base {
    private String Rele1;
    private String Rele2;
    private String Rele3;
    
    public base(){
        
    }

    public base(String Rele1, String Rele2, String Rele3) {
        this.Rele1 = Rele1;
        this.Rele2 = Rele2;
        this.Rele3 = Rele3;
    }

    public String getRele1() {
        return Rele1;
    }

    public void setRele1(String Rele1) {
        this.Rele1 = Rele1;
    }

    public String getRele2() {
        return Rele2;
    }

    public void setRele2(String Rele2) {
        this.Rele2 = Rele2;
    }

    public String getRele3() {
        return Rele3;
    }

    public void setRele3(String Rele3) {
        this.Rele3 = Rele3;
    }

    @Override
    public String toString() {
        return "base{" + "Rele1=" + Rele1 + ", Rele2=" + Rele2 + ", Rele3=" + Rele3 + '}';
    }
    
    public void registrar() {
        String json = "";
        try {
            BufferedReader br = new BufferedReader(new FileReader("almacena.json"));
            
            String linea;
            while((linea = br.readLine()) != null){
                json += linea;
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(base.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(base.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Gson gson = new Gson();
        base b = gson.fromJson(json, base.class);
        b.setRele1(Interfaz.jTextField1.getText());
       // System.out.println(b);
    }
    
    public void registrar2() {
        String json = "";
        try {
            BufferedReader br = new BufferedReader(new FileReader("almacena.json"));
            
            String linea;
            while((linea = br.readLine()) != null){
                json += linea;
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(base.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(base.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Gson gson = new Gson();
        base b = gson.fromJson(json, base.class);
        b.setRele2(Interfaz.jTextField2.getText());
      //  System.out.println(b);
    }
    public void registrar3() {
        String json = "";
        try {
            BufferedReader br = new BufferedReader(new FileReader("almacena.json"));
            
            String linea;
            while((linea = br.readLine()) != null){
                json += linea;
            }
        } catch (FileNotFoundException ex) {
            Logger.getLogger(base.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(base.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Gson gson = new Gson();
        base b = gson.fromJson(json, base.class);
        b.setRele3(Interfaz.jTextField3.getText());
      //  System.out.println(b);
    }
      
}
