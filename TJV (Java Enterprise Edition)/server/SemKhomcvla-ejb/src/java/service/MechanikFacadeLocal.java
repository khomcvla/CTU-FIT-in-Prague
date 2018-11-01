/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package service;

import db.Mechanik;
import java.util.List;
import javax.ejb.Local;

/**
 *
 * @author homya
 */
@Local
public interface MechanikFacadeLocal {

    void create(Mechanik mechanik);

    void edit(Mechanik mechanik);

    void remove(Mechanik mechanik);

    Mechanik find(Object id);

    List<Mechanik> findAll();

    List<Mechanik> findRange(int[] range);

    int count();
    
}
