/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package service;

import db.Auto;
import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author homya
 */
@Local
public interface AutoFacadeLocal {

    void create(Auto auto);

    void edit(Auto auto);

    void remove(Auto auto);

    Auto find(Object id);

    List<Auto> findAll();

    List<Auto> findRange(int[] range);

    int count();
    
}
